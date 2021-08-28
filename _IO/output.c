#include "../includes/libshell.h"

t_cut_cmd	*node_match(t_cut_cmd **target, t_cut_cmd *to_find)
{
	int	i;
	
	i = 0;
	while (target && target[i])
	{
		if (target[i] == to_find)
			return (target[i]);
		i++;
	}
	return (NULL);
}

int	is_output(t_cut_cmd **cmd)
{
	t_cut_cmd *save;

	save = (*cmd);
//	printf("[//%s]\n", (*cmd)->elem);
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
	register int deep;

	deep = 1;
	while ((*(cmd)) && (*(cmd))->TOKEN != CLOSED_DIV)
		(*(cmd)) = (*(cmd))->p;
	if (*cmd)
	{
		while (deep)
		{
			(*(cmd)) = (*(cmd))->p;
			deep--;
		}
		if ((*cmd))
		{
			if ((*(cmd))->TOKEN == R_REDIR || (*(cmd))->TOKEN == D_R_REDIR)
				return (SUCCESS);
		}
	}
	return (ERROR);
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
				if (flag("TRUNC_NEXT == true"))
					ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT | O_TRUNC, 0666));

				ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT | O_APPEND, 0666));
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
		flag("push TRUNC_NEXT=false");
		return (SUCCESS);
	}
	return (ERROR);
}

int	output_redirection(t_msh *msh, t_cut_cmd *cmd)
{
	//if (node_match(msh->tools->flag_map, cmd))
	if (msh->tools->flag_map && msh->tools->flag_map[0] == cmd)
		flag("push TRUNC_NEXT=true");
	if (is_output(&cmd) == SUCCESS)
	{
		while ((cmd != NULL && cmd->TOKEN != PIPE) && (cmd->TOKEN == ARG
				|| cmd->TOKEN == R_REDIR || cmd->TOKEN == D_R_REDIR))
		{
			if (cmd->TOKEN == ARG && cmd->n->TOKEN == R_REDIR)
			{
				ft_open(&msh->tools->fdout, open(cmd->elem, O_RDWR | O_CREAT | O_TRUNC, 0666));
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
