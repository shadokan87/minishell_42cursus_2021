#include "../../includes/libshell.h"

int	p_p_ready_to_process(t_msh *msh)
{
	t_cut_cmd	*iter;

	iter = msh->tools->head;
	while (iter && !msh->tools->error_msg)
	{
		if ((iter->TOKEN == OPEN_DIV && iter->n)
			&& !is_match("&&:||:(", ':', iter->n->elem))
			msh->tools->error_msg
				= ft_strjoin("operand missing before: ", iter->elem);
		else if ((iter->TOKEN == CLOSED_DIV && iter->p)
			&& !is_match("&&:||:)", ':', iter->p->elem))
			msh->tools->error_msg
				= ft_strjoin("operand missing after: ", iter->elem);
		else if ((iter->TOKEN == AND)
			&& (is_match("&", ':', iter->elem)))
			msh->tools->error_msg = p_near("&");
		iter = iter->n;
	}
	return ((msh->tools->error_msg == NULL));
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
