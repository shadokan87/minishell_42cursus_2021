#include "../../includes/libshell.h"

int	p_p_syntax_exceptions(t_msh *msh)
{
	return ((msh->tools->error_msg == NULL));
}



int	p_p_ready_to_process(t_msh *msh)
{
	t_cut_cmd	*iterator;

	iterator = msh->tools->head;
	while (iterator && !msh->tools->error_msg)
	{
		if ((iterator->TOKEN == OPEN_DIV && iterator->n)
			&& !is_match(SYMBOL_ALLOWED_BEFORE_OPEN_DIV, ':', iterator->n->elem))
			msh->tools->error_msg
				= ft_strjoin("operand missing before: ", iterator->elem);
		else if ((iterator->TOKEN == CLOSED_DIV && iterator->p)
			&& !is_match(SYMBOL_ALLOWED_AFTER_CLOSED_DIV, ':', iterator->p->elem))
			msh->tools->error_msg
				= ft_strjoin("operand missing after: ", iterator->elem);
		else if ((iterator->TOKEN == AND)
			&& (is_match("&", ':', iterator->elem)))
			msh->tools->error_msg = p_near("&");
		else if ((iterator->TOKEN == AND) && iterator->p->TOKEN == CLOSED_DIV)
			msh->tools->error_msg = p_near(")");
		iterator = iterator->n;
	}
	return (p_p_syntax_exceptions(msh));
}

int	p_p_check_par_join(t_msh *msh)
{
	char		*to_check;
	t_cut_cmd	*ptr;

	to_check = NULL;
	ptr = msh->tools->tail;
	while (ptr)
	{
		if (ptr->TOKEN != S_QUOTE && ptr->TOKEN != D_QUOTE)
		{
			if (!to_check)
				to_check = ft_strdup(ptr->elem);
			else
				to_check = ft_strjoin(to_check, ft_strjoin(" ", ptr->elem));
		}
		ptr = ptr->p;
	}
	if (to_check)
		return (p_check_par(msh, to_check));
	return (0);
}
