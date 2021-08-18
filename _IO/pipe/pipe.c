#include "../../includes/libshell.h"
#define $PRINT_LIST(x) t_cut_cmd *iterator;iterator = x;while(iterator){ft_putstr_fd(iterator->elem, 1);ft_putstr_fd("\n", 1);iterator = iterator->p;}

void	ispipe(t_msh *msh)
{
	t_cut_cmd	*cmd;
	int			cpt;

	cmd = msh->tools->tail;
	cpt = 0;
	while (cmd != NULL)
	{
		if (cmd->TOKEN == PIPE)
			cpt++;
		cmd = cmd->p;
	}
	msh->tools->nbpipe = cpt;
}

int	getnext_pipe(t_cut_cmd **cmd)
{
	while ((*(cmd)) != NULL && (*(cmd))->TOKEN != PIPE)
		(*(cmd)) = (*(cmd))->p;
	if ((*(cmd)) != NULL)
		(*(cmd)) = (*(cmd))->p;
	while ((*cmd)!= NULL && (*cmd)->TOKEN == OPEN_DIV)
		(*(cmd)) = (*(cmd))->p;
	if ((*(cmd)))
		return (SUCCESS);
	else
		return (-1);
}

void	whatpostions(t_msh *msh)
{
	t_cut_cmd	*cmd;
	t_cut_cmd	*tmp;

	cmd = msh->tools->tail;
	while (cmd != NULL)
	{
		tmp = cmd;
		if (getnext_pipe(&cmd) == -1)
			tmp->is_last = 1;
	}
}
