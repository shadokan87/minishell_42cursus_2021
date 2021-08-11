/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 05:43:06 by motoure           #+#    #+#             */
/*   Updated: 2021/08/08 05:47:06 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./wildcards.h"

int	MATCH(char *s1, char *s2, char *mode)
{
	int	ST_START_WTH;
	int	ST_CONTAIN;
	int	ST_END_WITH;

	ST_START_WTH = ((is_same(mode, "START_WITH"))
			&& ((ft_strlen(s2) >= ft_strlen(s1))
				&& (is_same((ft_strndup((s2), ft_strlen(s1))), s1))));
	ST_CONTAIN = ((is_same(mode, "CONTAIN"))
			&& ft_strlen(s2) >= ft_strlen(s1)
			&& ft_strnstr(s2, s1, ft_strlen(s2)));
	ST_END_WITH = ((is_same(mode, "END_WITH"))
			&& (ft_strlen(s2) >= ft_strlen(s1))
			&& (is_same(ft_strrev(ft_strndup(ft_strrev(s2),
							ft_strlen(s1))), s1)));
	if (ST_START_WTH || ST_CONTAIN || ST_END_WITH)
		return (ft_strlen(s1));
	return (0);
}

t_cut_cmd	**MATCH_END_WITH(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", NULL);
	while (ls)
	{
		if (MATCH(str, ft_strdup(ls->elem), "END_WITH"))
			add(msh, ls->elem, ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}

t_cut_cmd	**MATCH_ALL(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	(void)str;
	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", NULL);
	while (ls)
	{
		add(msh, ls->elem, ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}

t_cut_cmd	**MATCH_START_WITH(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", "-a");
	while (ls)
	{
		if (MATCH(str, ls->elem, "START_WITH"))
			add(msh, (ls->elem), ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}

t_cut_cmd	**MATCH_CONTAIN(t_msh *msh, char *str)
{
	t_cut_cmd	**ret;
	t_cut_cmd	*ls;

	ret = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
	if (!ret)
		return (NULL);
	head_tail(msh, "backup");
	ls = ft_ls(".", "-a");
	while (ls)
	{
		if (MATCH(str, ls->elem, "CONTAIN"))
			add(msh, (ls->elem), ARG);
		ls = ls->n;
	}
	ret[0] = msh->tools->head;
	ret[1] = msh->tools->tail;
	head_tail(msh, "restore");
	return (ret);
}
