#include "../includes/libshell.h"

static int	is_in(t_cut_cmd *cmd, char *mode)
{
	t_cut_cmd *iterator;

	iterator = cmd;
	while (iterator)
	{
		if (iterator->TOKEN == CLOSED_DIV && is_same(mode, "DIV"))
			return (0);
		if (iterator->TOKEN == OPEN_DIV && is_same(mode, "DIV"))
			return (1);
		if (iterator->TOKEN == AND && is_same(mode, "AND"))
			return (1);
		iterator = iterator->n;
	}
	return (0);
}

int	check_div_redir(t_cut_cmd *cmd)
{
	t_cut_cmd *iterator;

	if (!is_in(cmd, "DIV"))
		return (ERROR);
	iterator = cmd;
	while (iterator && iterator->TOKEN != CLOSED_DIV)
		iterator = iterator->p;
	iterator = iterator->p;
	if (iterator->TOKEN == R_REDIR || iterator->TOKEN == L_REDIR
			|| iterator->TOKEN == D_R_REDIR)
			return (SUCCESS);
	return (ERROR);
}

int	isredir(t_cut_cmd *cmd)
{
	while (cmd != NULL && cmd->TOKEN != PIPE && cmd->TOKEN != OR && cmd->TOKEN != AND)
	{
		if (cmd->TOKEN == R_REDIR || cmd->TOKEN == L_REDIR
			|| cmd->TOKEN == D_R_REDIR)
			return (SUCCESS);
		cmd = cmd->p;
	}
	return (check_div_redir(cmd));
}

void	set_cmd_end(t_cut_cmd **cmd)
{
	while ((*cmd))
	{
		if ((*cmd)->TOKEN == OR || (*cmd)->TOKEN == AND)
		{
			(*cmd) = NULL;
			return ;
		}
		(*cmd) = (*cmd)->p;
	}
}

int	set_div_fd(t_msh *msh, t_cut_cmd *cmd, int fd)
{
	(void)msh;
	(void)cmd;
	(void)fd;
	if (!cmd->is_last)
		dup2(msh->tools->pipe[1], 1);
	return (SUCCESS);
}

int	handle_redirection(t_msh *msh, t_cut_cmd *cmd, int fd)
{
	int ret;

	ret = isredir(cmd);
	if ((ret == -1) && (fd >= 0))
	{
		if (!cmd->is_last)
			dup2(msh->tools->pipe[1], 1);
		return (SUCCESS);
	}
	else
	{
		msh->tools->fdin = 0;
		msh->tools->fdout = 0;
		msh->tools->b_stdout = dup(STDOUT_FILENO);
		input_redirection(msh, cmd);
		output_redirection(msh, cmd);
	}
	return (SUCCESS);
}
