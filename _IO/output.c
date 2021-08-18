#include "../includes/libshell.h"

int	is_output(t_cut_cmd **cmd)
{
	t_cut_cmd *save;

	save = (*cmd);
	while ((*(cmd)) && (*(cmd))->TOKEN != PIPE)
	{
		if ((*cmd)->TOKEN == OR || (*cmd)->TOKEN == AND
			|| (*cmd)->TOKEN == CLOSED_DIV || (*cmd)->TOKEN == OPEN_DIV)
			break ;
		if ((*(cmd))->TOKEN == R_REDIR || (*(cmd))->TOKEN == D_R_REDIR)
			return (SUCCESS);
		(*(cmd)) = (*(cmd))->p;
	}
	return (ERROR);
}

int	is_div_output(t_cut_cmd **cmd)
{
	while ((*(cmd)) && (*(cmd))->TOKEN != CLOSED_DIV)
		(*(cmd)) = (*(cmd))->p;
	if (*cmd)
	{
		(*(cmd)) = (*(cmd))->p;
		if ((*(cmd))->TOKEN == R_REDIR || (*(cmd))->TOKEN == D_R_REDIR)
			return (SUCCESS);
	}
	return (ERROR);
}

void	print_list_msg(t_cut_cmd *print, char *message)
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
		print = print->n;
	}
}

char	*flag(char *instr)
{
	static t_cut_cmd	*flags;
	t_cut_cmd			*try;
	char				*to_add;

	if (is_same(instr, "print"))
		print_list_msg(flags, "\nFLAG");
	if (is_same("status", instr))
		return ((char *)flags);
	to_add = ft_split(instr, ' ')[1];
	if (is_same(ft_split(instr, ' ')[0], "push"))
	{
		gc("pause");
		try = get_env_of(flags, to_add);
		if (try)
			try->elem = to_add;
		else if (ft_split(instr, ' ')[0])
			add_to_env(&flags, to_add, _UNASSIGNED);
		gc("resume");
	}
	else if (is_same(ft_split(instr, ' ')[0], "get"))
		return (get_val_from_var(get_env_of(flags, to_add)));
	return (NULL);
}

int	div_output_redirection(t_msh *msh, t_cut_cmd *cmd)
{
	if (is_div_output(&cmd) == SUCCESS)
	{
		while ((cmd != NULL && cmd->TOKEN != PIPE) && (cmd->TOKEN == ARG
				|| cmd->TOKEN == R_REDIR || cmd->TOKEN == D_R_REDIR))
		{
			if (cmd->TOKEN == ARG && cmd->n->TOKEN == R_REDIR)
			{
				ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666));
				if (msh->tools->fdout < 0)
					append_error(msh, cmd, NULL, errno);
			}
			else if (cmd->TOKEN == ARG && cmd->n->TOKEN == D_R_REDIR)
			{
				ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT | O_APPEND | ft_atoi(flag("get O_TRUNC")), 0666));
				msh->tools->tail->fd_flag = 0;
				if (msh->tools->fdout < 0)
					append_error(msh, cmd, NULL, errno);
			}
			cmd = cmd->p;
		}
		dup2(msh->tools->fdout, 1);
		return (SUCCESS);
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
				ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT, 0666));
				if (msh->tools->fdout < 0)
					append_error(msh, cmd, NULL, errno);
			}
			else if (cmd->TOKEN == ARG && cmd->n->TOKEN == D_R_REDIR)
			{
				ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666));
				if (msh->tools->fdout < 0)
					append_error(msh, cmd, NULL, errno);
			}
			cmd = cmd->p;
		}
		dup2(msh->tools->fdout, 1);
		return (SUCCESS);
	}
	return (div_output_redirection(msh, cmd));
}
