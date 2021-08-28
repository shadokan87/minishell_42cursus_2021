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
	if ((*pos)->n && (*pos)->n->TOKEN == CLOSED_DIV)
	{
		msh->tools->flag_map = NULL;
		flag("NULL");
	}
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
	if ((*pos)->n && (*pos)->n->TOKEN == CLOSED_DIV)
	{
		msh->tools->flag_map = NULL;
		flag("NULL");
	}
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
	msh->tools->flag_map = NULL;
	flag("NULL");
	return (1);
}

void	move_pos(t_msh *msh, t_cut_cmd **pos)
{
	(void)msh;
	while ((*pos) && ((*pos)->TOKEN >= C_BUILTIN && (*pos)->TOKEN <= WILD_CARD))
		(*pos) = (*pos)->p;
	ft_open(&msh->tools->fdout, -1);
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
    if (!pos)
        return (NULL);
    if (flag("SKZERO == true")
        && iterator->TOKEN == TOKEN)
        iterator = iterator->p;
	while (iterator)
	{
		if (((iterator->TOKEN == AND && flag("SKAND != true"))
			|| (iterator->TOKEN == OR && flag("SKOR != true"))
			|| (iterator->TOKEN == CLOSED_DIV && flag("SKCDIV != true"))
			|| (iterator->TOKEN == OPEN_DIV && flag("SKODIV != true"))))
			break ;
		if (iterator->TOKEN == TOKEN)
			return (iterator);
		iterator = iterator->p;
    }
	return (NULL);
}

t_TOKEN		scope_contain_redir(t_cut_cmd *pos)
{
	t_TOKEN     try;
	t_cut_cmd   *get_next_token_try;

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

typedef struct s_deep
{
    int deep;
    t_cut_cmd *in;
    t_cut_cmd *out;
}               t_deep;

void		map_flags(t_msh *msh, t_cut_cmd *pos)
{
	int			insert_pos;
	int			inserted;
	t_cut_cmd	*iterator;

	if (msh->tools->flag_map || !is_in_div(pos))
		return ;
	iterator = pos;
	insert_pos = 0;
	inserted = 0;
	msh->tools->flag_map = ft_calloc(list_len(pos), sizeof(t_cut_cmd *) * list_len(pos));
	while (iterator)
	{
		if (is_in_div(iterator))
		{
			if (scope_contain_redir(iterator) == _UNASSIGNED)
			{
				if ((iterator->TOKEN == C_BUILTIN || iterator->TOKEN == C_ENV) && !inserted)
				{
					msh->tools->flag_map[insert_pos] = iterator;
					inserted = 1;
					insert_pos++;
				}
			}
		}
		iterator = iterator->p;
	}
}

int    get_deep(t_cut_cmd *pos, int deep)
{
    while (pos)
    {
        if (pos->TOKEN == CLOSED_DIV)
            break ;
        else if (pos->TOKEN == OPEN_DIV)
            deep++;
        pos = pos->p;
    }
    return (deep);
}

t_deep get_deep2(t_cut_cmd *pos)
{
    t_deep deep;
    int tmp;

    deep.deep = get_deep(pos, 1);
    deep.in = pos;
    tmp = deep.deep;
    while (tmp && pos)
    {
        if (tmp == 1)
            deep.out = pos;
        if (pos->TOKEN == CLOSED_DIV)
            tmp--;
        pos = pos->p;
    }
    (void)pos;
    return (deep);
}
/*
void    skip_misuse(t_msh *msh, t_cut_cmd **pos)
{
    (void)msh;
    t_deep      deep;
    int         deep_copy;
    int         level_check;
    t_cut_cmd   *jmp;

    if (!(*pos) || !is_in_div((*pos)))
        return ;
    deep = get_deep2((*pos));
    if (deep.deep == 1)
        return ;
    level_check = 0;
    deep_copy = deep.deep;
    flag_loop("push SKCDIV=true:push SKODIV=true:push SKZERO=true:push SKAND=true:push SKOR=true");
    jmp = (*pos);
    while (deep_copy)
    {
        jmp = get_next_token_scope(jmp, CLOSED_DIV);
        printf("[%s]\n", jmp->p->elem);
        $BR
        if (get_next_token_scope(jmp, AND) || get_next_token_scope(jmp, OR))
            level_check++;
        deep_copy--;
    }
    flag_loop("push SKCDIV=false:push SKODIV=false:push SKZERO=false:push SKAND=false:push SKOR=false");
    printf("[%d] [%d]\n", deep.deep, level_check);
    if (!(level_check == deep.deep - 1))
    {
        printf("EXIT\n");
        $BR
    }
    else
        flag("push DEEP=wait");
}
*/
int         handle_cmd(t_msh *msh, t_cut_cmd *pos)
{
	write_error(msh);
   // if (flag("DEEP != wait"))
  //  skip_misuse(msh, &pos);
	msh->tools->tail = pos;
	if (!msh || !pos || !msh->tools->tail)
		return (-1);
	msh->tools->noforked_exit = 0;
	ispipe(msh);
	map_flags(msh, pos);
	whatpostions(msh);
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
