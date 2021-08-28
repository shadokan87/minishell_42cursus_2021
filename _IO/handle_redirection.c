#include "../includes/libshell.h"


static void	print_list_msg2(t_cut_cmd *print, char *message)
{
	while (print)
	{
		if (message)
		{
			ft_putstr_fd(ft_strjoin(message, ": "), 1);
			ft_putstr_fd("\n", 1);
		}
		ft_putstr_fd(print->elem, 1);
		$MSG("\n")
			print = print->p;
	}
}

int	isredir(t_cut_cmd *cmd)
{
	while (cmd != NULL && cmd->TOKEN != PIPE)
	{
		if (cmd->TOKEN == OR || cmd->TOKEN == AND)
			break ;
		if (cmd->TOKEN == R_REDIR || cmd->TOKEN == L_REDIR
			|| cmd->TOKEN == D_R_REDIR)
			return (SUCCESS);
		cmd = cmd->p;
	}
	return (ERROR);
}

int	handle_redirection(t_msh *msh, t_cut_cmd *cmd, int fd)
{
	int	ret;

	print_list_msg2(NULL, NULL);
	ret = isredir(cmd);
	if ((ret == -1) && (fd >= 0))
	{
		if (!cmd->is_last)
			dup2(msh->tools->pipe[1], 1);
		return (SUCCESS);
	}
	else
	{
		ft_open(&msh->tools->fdin, -1);
		ft_open(&msh->tools->fdout, -1);
		msh->tools->b_stdout = dup(STDOUT_FILENO);
		input_redirection(msh, cmd);
		output_redirection(msh, cmd);
	}
	return (SUCCESS);
}
