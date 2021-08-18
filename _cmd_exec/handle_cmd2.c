#include "../includes/libshell.h"

/*
int	_placeholder_handle_cmd(t_msh *msh)
{
	t_cut_cmd	*pos;

	if (msh->tools->error_msg)
		return (0);
	init_pos(msh->tools->tail, &pos);
	handle_cmd(msh, pos);
	return (1);
}

void	move_pos(t_msh *msh, t_cut_cmd **pos)
{
	(void)msh;
	while ((*pos) && ((*pos)->TOKEN >= C_BUILTIN && (*pos)->TOKEN <= WILD_CARD))
		(*pos) = (*pos)->p;
}

int	goto_next_div(t_msh *msh, t_cut_cmd **pos)
{
	(*pos) = (*pos)->p;
	if ((*pos) && (*pos)->TOKEN == OR)
	{
		if ((*pos)->p && (*pos)->p->TOKEN != OPEN_DIV && msh->tools->status)
		{
			(*pos) = (*pos)->p;
			return (1);
		}
		while ((*pos))
		{
			if ((*pos) && ((*pos)->TOKEN == AND)
				&& ((*pos)->n->TOKEN == CLOSED_DIV))
				break ;
			else if ((msh->tools->status)
				&& ((*pos) && (*pos)->n->TOKEN == OPEN_DIV))
				break ;
			(*pos) = (*pos)->p;
		}
	}
	return (1);
}
*/
