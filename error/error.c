/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:55:19 by motoure           #+#    #+#             */
/*   Updated: 2021/08/23 05:26:50 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libshell.h"

static int	_deprecated_add_to_env(t_cut_cmd **target, char *elem, t_TOKEN TOKEN)
{
	t_cut_cmd	*ret;

	ret = fill(elem, TOKEN);
	if (!*target)
	{
		*target = ret;
		return (1);
	}
	ret->n = *target;
	(*target)->p = ret;
	*target = ret;
	return (1);
}

int append_error(t_msh *msh, t_cut_cmd *cmd, char *msg, int ret)
{
	(void)msh;
	(void)cmd;
	(void)msg;
	if (msh->tools->status)
		_deprecated_add_to_env(&msh->tools->errors, msg, _UNASSIGNED);
	return (ret);
}

void	write_error(t_msh *msh)
{
	if (msh->tools->error_msg)
	{
		write(2, msh->tools->error_msg, ft_strlen(msh->tools->error_msg));
		write(2, "\n", 1);
	}
	if (msh->tools->errors)
		print_split(list_to_split(msh->tools->errors), "rev");
	msh->tools->error_msg = NULL;
	msh->tools->errors = NULL;
}

void	handler(int n)
{
	(void)n;
	gc("collect -all");
	exit (0);
}
