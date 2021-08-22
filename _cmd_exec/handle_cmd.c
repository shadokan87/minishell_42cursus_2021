#include "../includes/libshell.h"

t_cut_cmd	*is_in_div(t_cut_cmd *pos)
{
	t_cut_cmd *iterator;

	iterator = pos;
	while (iterator)
	{
		if (iterator->TOKEN == OPEN_DIV)
			return (iterator->p);
		iterator = iterator->n;
	}
	return (NULL);
}

int	catch_and(t_msh *msh, t_cut_cmd **pos)
{
	register int	deep;

	deep = 0;
	if ((*pos)->TOKEN != AND)
		return (0);
	if (!msh->tools->status)
		(*pos) = (*pos)->p;
	while (msh->tools->status && (*pos))
	{
		if ((*pos)->TOKEN == OPEN_DIV)
			deep++;
		if ((*pos)->TOKEN == OR && !deep)
			break ;
		(*pos) = (*pos)->p;
	}
	return (1);
}

int	catch_or(t_msh *msh, t_cut_cmd **pos)
{
	register int	deep;
	
	deep = 0;
	if ((*pos)->TOKEN != OR)
		return (0);
	if (msh->tools->status)
		(*pos) = (*pos)->p;
	while (!msh->tools->status && (*pos))
	{
		if ((*pos)->TOKEN == OPEN_DIV)
			deep++;
		if ((*pos)->TOKEN == AND && !deep)
			break ;
		(*pos) = (*pos)->p;
	}
	return (1);
}

void	init_pos(t_cut_cmd *tail, t_cut_cmd **pos)
{
	if (tail && tail->TOKEN == OPEN_DIV)
		(*pos) = tail->p;
	else
		(*pos) = tail;
}

int		_placeholder_handle_cmd(t_msh *msh)
{
	t_cut_cmd *pos;

	(void)msh;
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

int			goto_next_div(t_msh *msh, t_cut_cmd **pos)
{
	(void)msh;
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
			if ((*pos) && ((*pos)->TOKEN == AND) && ((*pos)->n->TOKEN == CLOSED_DIV))
				break ;
		else if ((msh->tools->status) && ((*pos) && (*pos)->n->TOKEN == OPEN_DIV))
			break ;
			(*pos) = (*pos)->p;
		}
	}
	return (1);
}

t_cut_cmd	*get_next_token_scope(t_cut_cmd *pos, t_TOKEN TOKEN)
{
	t_cut_cmd *iterator;

	iterator = pos;
	while (iterator)
	{
		if (iterator->TOKEN != TOKEN && (iterator->TOKEN == AND
			|| iterator->TOKEN == OR
			|| iterator->TOKEN == CLOSED_DIV
			|| iterator->TOKEN == OPEN_DIV))
			break ;
		if (iterator->TOKEN == TOKEN)
			return (iterator);
		iterator = iterator->p;
	}
	return (NULL);
}

t_TOKEN		scope_contain_redir(t_cut_cmd *pos)
{
	t_TOKEN	try;
	t_cut_cmd *get_next_token_try;

	try = R_REDIR;
	while (try <= D_L_REDIR)
	{
		get_next_token_try = get_next_token_scope(pos, try);
		if (get_next_token_try)
			return (try);
		try++;
	}
	return (_UNASSIGNED);
}

void		place_flag(t_cut_cmd *pos)
{
	if (is_in_div(pos) && (scope_contain_redir(pos) == _UNASSIGNED))
	{
		if (flag("TRUNC_WAIT == true"))
			return ;
		$MSG("done")
		flag(ft_strjoin("push O_TRUNC=", ft_itoa(O_TRUNC)));
		flag("push TRUNC_WAIT=true");
	}
}

int         handle_cmd(t_msh *msh, t_cut_cmd *pos)
{
	write_error(msh);
	msh->tools->tail = pos;
	if (!msh || !pos || !msh->tools->tail)
		return (-1);
	msh->tools->noforked_exit = 0;
	ispipe(msh);
	whatpostions(msh);
//	place_flag(pos);
	if (msh->tools->nbpipe > 0)
		cmd_pipe(msh, pos);
	else
		cmd_nopipe(msh, pos);
	move_pos(msh, &pos);
	if (((pos) && (catch_and(msh, &pos) || catch_or(msh, &pos))))
		return (handle_cmd(msh, pos));
	if ((pos) && goto_next_div(msh, &pos))
		return (handle_cmd(msh, pos));
	return (0);
}
