#include "../../includes/libshell.h"

t_cut_cmd	**head_tail(t_msh *msh, char *mode)
{
	static t_cut_cmd	**bak;

	if (!bak)
		bak = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (is_same(mode, "backup") && !bak[0] && !bak[1])
	{
		bak[0] = msh->tools->head;
		bak[1] = msh->tools->tail;
		msh->tools->head = NULL;
		msh->tools->tail = NULL;
	}
	else if (is_same(mode, "restore"))
	{
		msh->tools->head = bak[0];
		msh->tools->tail = bak[1];
		bak = NULL;
	}
	return (bak);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	*msh;

	gc_init();
	(void)argc;
	(void)argv;
	gc("pause");
	init_msh(&msh, envp);
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
