#include "../includes/libshell.h"

int	is_output(t_cut_cmd **cmd)
{
	while ((*(cmd)) && (*(cmd))->TOKEN != PIPE)
	{
		if ((*(cmd))->TOKEN == R_REDIR || (*(cmd))->TOKEN == D_R_REDIR)
			return (SUCCESS);
		(*(cmd)) = (*(cmd))->p;
	}
	return (ERROR);
}

int	output_redirection(t_msh *msh, t_cut_cmd *cmd)
{
	if (is_output(&cmd) == SUCCESS)
	{
		while ((cmd != NULL && cmd->TOKEN != PIPE) && (cmd->TOKEN == ARG
				|| cmd->TOKEN == R_REDIR || cmd->TOKEN == D_R_REDIR))
		{
			if (cmd->TOKEN == ARG && cmd->n->TOKEN == R_REDIR)
			{
				msh->tools->fdout = open(cmd->elem, O_RDWR | O_CREAT, 0666);
				if (msh->tools->fdout < 0)
					ft_error(msh, cmd, NULL, errno);
			}
			else if (cmd->TOKEN == ARG && cmd->n->TOKEN == D_R_REDIR)
			{
				msh->tools->fdout
					= open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666);
				if (msh->tools->fdout < 0)
					ft_error(msh, cmd, NULL, errno);
			}
			cmd = cmd->p;
		}
		dup2(msh->tools->fdout, 1);
		return (SUCCESS);
	}
	return (ERROR);
}
