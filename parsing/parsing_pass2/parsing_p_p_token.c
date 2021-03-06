#include "../../includes/libshell.h"

t_TOKEN	p_p_determine_symbol(char *elem)
{
	static char	**lookup_table;
	int		*token_index;
	int		table_len;
	int		i;

	i = 0;
	lookup_table = ft_split(SYMBOL_DETERMINE, ' ');
	table_len = split_len(lookup_table);
	token_index = gc_malloc(sizeof(int) * table_len);
	if (!token_index)
		return (0);
	table_len = PIPE;
	while (table_len < _END)
	{
		token_index[i] = table_len;
		table_len++;
		i++;
	}
	i = 0;
	while (lookup_table[i] && !is_match(lookup_table[i], ' ', elem))
		i++;
	if (lookup_table[i])
		return (token_index[i]);
	return (_UNASSIGNED);
}

t_TOKEN	p_p_determine_cmd(char *elem, int cmd_re_eval)
{
	(void)cmd_re_eval;
	if (is_builtin(elem) && cmd_re_eval)
		return (C_BUILTIN);
	else if (elem[0] == '-')
		return (OPTION);
	else if (!cmd_re_eval)
		return (ARG);
	return (C_ENV);
}

int	check_exception(t_cut_cmd **tail)
{
	t_cut_cmd *iterator;

	iterator = (*tail);
	while (iterator)
	{
		if (iterator->TOKEN == R_REDIR && (iterator->n && iterator->n->TOKEN == CLOSED_DIV))
		{
			while (iterator)
			{
				if (iterator->TOKEN == AND || iterator->TOKEN == OR ||
					iterator->TOKEN == CLOSED_DIV ||
					iterator->TOKEN == OPEN_DIV)
				{
					if (iterator->TOKEN == OPEN_DIV)
						iterator->p->fd_flag = O_TRUNC;
					break ;
				}
				if (iterator->TOKEN == R_REDIR)
					iterator->TOKEN = D_R_REDIR;
				iterator = iterator->p;
			}
			if (iterator)
				return (check_exception(tail));
			return (1);
		}
		iterator = iterator->p;
	}
	return (1);
}

int	p_p_determine_token(t_msh *msh)
{
	t_cut_cmd	*iter;
	int			cmd_re_eval;

	iter = msh->tools->tail;
	cmd_re_eval = 1;
	while (iter && !msh->tools->error_msg)
	{
		if (iter->TOKEN == _UNASSIGNED
			&& is_match(SYMBOL_DETERMINE, ' ', iter->elem))
		{
			iter->TOKEN = p_p_determine_symbol(iter->elem);
			if (iter->TOKEN == OPEN_DIV || iter->TOKEN == CLOSED_DIV
				|| iter->TOKEN == OR || iter->TOKEN == AND)
				cmd_re_eval = 1;
		}
		else if (iter->TOKEN == _UNASSIGNED)
		{
			iter->TOKEN = p_p_determine_cmd(iter->elem, cmd_re_eval);
			cmd_re_eval = 0;
		}
		iter = iter->p;
	}
	return (1);
	//return (check_exception(&msh->tools->tail));
}
