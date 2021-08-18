#include "../includes/libshell.h"

void	cmd_nopipe(t_msh *msh, t_cut_cmd *cmd)
{
	(void)cmd;
	(void)msh;
	if (cmd && cmd->TOKEN == C_BUILTIN)
		handle_builtins(msh, cmd);
	else if (cmd && cmd->TOKEN == C_ENV)
		simple_exec(msh, cmd);
}

void	son_fork(t_msh *msh, t_cut_cmd *cmd, int bfd)
{
	char	*exec_path;
	char	**args;

	dup2(bfd, 0);
	handle_redirection(msh, cmd, bfd);
	if (cmd && cmd->TOKEN == C_BUILTIN)
		handle_builtins(msh, cmd);
	else
	{
		exec_path = _place_holder_get_path(msh, cmd);
		args = handle_args(msh, cmd);
		execve(exec_path, args, list_to_split(msh->env->head));
		exit (1);
	}
}

void	father_fork(t_msh *msh, t_cut_cmd *cmd, int pid, int *bfd)
{
	(void)cmd;
	waitpid(pid, &msh->tools->status, 0);
	if (bfd > 0)
	{
		close(msh->tools->pipe[1]);
		*bfd = msh->tools->pipe[0];
	}
	if ((open("./msh_heredoc.msh", O_RDONLY, 0666)) != -1)
		delete_heredoc(msh);
}

void	cmd_pipe(t_msh *msh, t_cut_cmd *cmd)
{
	int		pid;
	int		bfd;
	
	bfd = 0;
	while (cmd != NULL)
	{
		pipe(msh->tools->pipe);
		if ((cmd->p && cmd->p->TOKEN == C_BUILTIN) && is_same(cmd->elem, "export"))
			builtin_export(msh, cmd);
		else
		{
			pid = fork();
			if (pid == 0)
				son_fork(msh, cmd, bfd);
			else if (pid > 0)
				father_fork(msh, cmd, pid, &bfd);
			else
				append_error(msh, cmd, "PID NEGATIVE", 0);
		}
		getnext_pipe(&cmd);
	}
}
