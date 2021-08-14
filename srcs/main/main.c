#include "../../includes/libshell.h"

void	get_history_from_fd(int fd)
{
	char buff[2];
	char *ret;

	ret = NULL;
	while (read(fd, &buff, 1))
	{
		buff[1] = '\0';
		if (!ret)
			ret = ft_strdup(buff);
		else
			ret = ft_strjoin(ret, buff);
		if (buff[0] == '\n')
		{
			add_history(ret);
			ret = NULL;
		}
	}
	if (ret)
		add_history(ret);
}

int	init_history(t_msh *msh)
{
	(void)msh;
	char *ret;
	int i;
	t_cut_cmd	*home;

	i = -1;
	ret = NULL;
	home = get_env_of(msh->envp, "HOME");
	if (!home || split_len(ft_split(home->elem, '=')) != 2)
	{
		ft_putstr_fd("minishell: failed to get home path!\nhistory won't be working for current session\ndynamic prompt won't be working for current session", 2);
		return (0);
	}
	msh->tools->history_fd = open(ft_strjoin(ft_split(home->elem, '=')[1], "/.history.msh"), O_CREAT | O_RDWR | O_APPEND, 0666);
	if (msh->tools->history_fd == -1)
	{
		ft_putstr_fd("minishell: failed to initialize history\nhistory won't be saved at session exit", 2);
		return (0);
	}
	get_history_from_fd(msh->tools->history_fd);
	return (1);
}


int		init_shell(void)
{
	char bp[1024];

	if (tgetent(bp, getenv("minishell")) != 1)
	{
		ft_putstr_fd("minishell: initalization failed, exiting now", STDERR_FILENO);
		exit(255);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;

	init_shell();
	gc_init();
	(void)argc;
	(void)argv;
	gc("pause");
	init_msh(&msh, envp);
	init_history(msh);
	gc("resume");
	signal(SIGINT, handler);
	while (msh->tools->run_status)
	{
		get_line(msh, NULL);
		if (p_process_line(msh))
			_placeholder_handle_cmd(msh);
		write_error(msh);
		msh->jobs->have_been_read = (msh->jobs->reading_line = NULL);
		msh->tools->head = (msh->tools->tail = NULL);
		gc("collect");
	}
	gc("collect -all");
	return (0);
}
