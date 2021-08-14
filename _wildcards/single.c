/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:43:15 by motoure           #+#    #+#             */
/*   Updated: 2021/08/12 02:59:33 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcards.h"

void	substitute_wildcards(t_msh *msh, t_cut_cmd **pos)
{
	t_cut_cmd	**ret;

	(void)pos;
	ret = NULL;
	if ((*pos)->tail_wild_card->wild_card_type == W_START_WITH)
		ret = MATCH_START_WITH(msh, ft_strtrim((*pos)->elem, "*"));
	else if ((*pos)->tail_wild_card->wild_card_type == W_CONTAIN)
		ret = MATCH_CONTAIN(msh, ft_strtrim((*pos)->elem, "*"));
	else if ((*pos)->tail_wild_card->wild_card_type == W_END_WITH)
		ret = MATCH_END_WITH(msh, ft_strtrim((*pos)->elem, "*"));
	else if ((*pos)->tail_wild_card->wild_card_type == W_ALL)
		ret = MATCH_ALL(msh, NULL);
	if (ret)
	{
		(*pos)->head_wild_card = ret[0];
		(*pos)->tail_wild_card = ret[1];
	}
}
