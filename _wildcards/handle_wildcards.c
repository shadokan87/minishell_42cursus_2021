/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:43:02 by motoure           #+#    #+#             */
/*   Updated: 2021/08/12 02:58:07 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

static int	is_wildcard(t_msh *msh, t_cut_cmd **iterator, char *str)
{
	char	**split;

	if (!c_is_present(str, '*') || c_is_present(str, '/'))
		return (-1);
	head_tail(msh, "backup");
	split = keep_split(msh, str, '*', WILD_CARD);
	(*iterator)->head_wild_card = msh->tools->head;
	(*iterator)->tail_wild_card = msh->tools->tail;
	head_tail(msh, "restore");
	(*iterator)->TOKEN = WILD_CARD;
	_place_holder_determine_wildcard_type(msh, iterator);
	return (1);
}

static void	single_or_multiple(t_msh *msh, t_cut_cmd **pos)
{
	if (list_len((*pos)->tail_wild_card) == 1)
		substitute_wildcards(msh, pos);
	else
		substitute_wildcards_multiple(msh, pos);
}

static void	_place_holder_substitute_wildcards(t_msh *msh)
{
	t_cut_cmd	*pos;

	pos = msh->tools->tail;
	while (pos)
	{
		if (pos->tail_wild_card)
			single_or_multiple(msh, &pos);
		pos = pos->p;
	}
}

void	_place_holder_handle_wildcards(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*iterator;

	iterator = cmd;
	while (iterator)
	{
		is_wildcard(msh, &iterator, iterator->elem);
		iterator = iterator->p;
	}
	_place_holder_substitute_wildcards(msh);
}
