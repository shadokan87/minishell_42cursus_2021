/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:42:48 by motoure           #+#    #+#             */
/*   Updated: 2021/08/08 05:42:56 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

static int	determine_wildcard_type(t_msh *msh, t_cut_cmd **iterator, char *str)
{
	char	**try;

	(void)msh;
	try = ft_calloc(4, sizeof(char *) * 4);
	if (!c_is_present(str, '*') && !is_same(str, ""))
		return (((*iterator)->wild_card_type = W_END_WITH));
	try[W_START_WITH] = trim_right(ft_strdup(str), '*');
	try[W_CONTAIN] = trim_right(trim_left(ft_strdup(str), '*'), '*');
	try[W_END_WITH] = trim_left(ft_strdup(str), '*');
	if (!c_is_present(try[W_START_WITH], '*')
		&& !is_same(try[W_START_WITH], ""))
		return (((*iterator)->wild_card_type = W_START_WITH));
	else if (!c_is_present(try[W_END_WITH], '*')
		&& !is_same(try[W_START_WITH], ""))
		return (((*iterator)->wild_card_type = W_END_WITH));
	else if (!c_is_present(try[W_CONTAIN], '*')
		&& !is_same(try[W_CONTAIN], ""))
		return (((*iterator)->wild_card_type = W_CONTAIN));
	else if (is_same(try[W_START_WITH], ""))
		return (((*iterator)->wild_card_type = W_ALL));
	return (-1);
}

void	_place_holder_determine_wildcard_type(t_msh *msh, t_cut_cmd **iterator)
{
	t_cut_cmd	*iterator2;

	iterator2 = (*iterator)->tail_wild_card;
	(void)*iterator;
	while (iterator2)
	{
		determine_wildcard_type(msh, &iterator2, iterator2->elem);
		iterator2 = iterator2->p;
	}
}
