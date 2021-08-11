#include "../includes/libshell.h"

void	_place_holder_handle_expand_env(t_msh *msh, t_cut_cmd *cmd)
{
	(void)msh;
	(void)cmd;
}

char	*_place_holder_get_path(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*update_path;
	char		**tmp;
	char		*tmp2;

	(void)tmp;
	update_path = get_env_of(msh->envp, "PATH");
	gc_free_calloc(msh->path);
	msh->path = ft_split(ft_split(update_path->elem, '=')[1], ':');
	tmp2 = determine_path_type(cmd, ft_strdup(cmd->elem));
	if (tmp2)
	{
		tmp = ft_calloc(2, sizeof(char *) * 2);
		tmp[0] = tmp2;
		return (get_path(cmd, tmp));
	}	
	else
		return (get_path(cmd, msh->path));
}

void	delete_heredoc(t_msh *msh)
{
	t_cut_cmd	*to_delete;
	char		**delete_args;
	char		*to_delete_path;
	int			pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		to_delete = (t_cut_cmd *)malloc(sizeof(t_cut_cmd));
		to_delete->elem = ft_strdup("/bin/rm");
		to_delete_path = get_path(to_delete, list_to_split(msh->env->head));
		delete_args = ft_split("rm -rf ./msh_heredoc.msh", ' ');
		msh->tools->marker = NULL;
		execve(to_delete->elem, delete_args, list_to_split(msh->env->head));
		printf("[FORK FORK FAILED]\n");
	}
	else
		waitpid(pid2, &msh->tools->status, 0);
}

/* CHANGE -> ft_error(cmd, "-1 PID\n", 0); */
void	simple_exec(t_msh *msh, t_cut_cmd *cmd)
{
	int		pid;
	int		bfd;

	bfd = -1;
	pipe(msh->tools->pipe);
	if ((cmd->p && cmd->p->TOKEN == ARG) && is_same(cmd->elem, "export"))
		builtin_export(msh, cmd);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			son_fork(msh, cmd, bfd);
		}
		else if (pid > 0)
			father_fork(msh, cmd, pid, &bfd);
		else
			ft_error(msh, cmd, "-1 PID\n", 0);
	}
}
