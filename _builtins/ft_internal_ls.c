/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_internal_ls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 22:32:13 by motoure           #+#    #+#             */
/*   Updated: 2021/08/18 12:15:50 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./builtins.h"

static int	ft_readdir(struct dirent **de, DIR *dr)
{
	*de = readdir(dr);
	return ((*de != NULL));
}

void	ft_open(int *ret, int fd)
{
	if (*ret != -1 && *ret != 0 && *ret != 1)
		close(*ret);
	if (fd != -1)
		*ret = fd;
}

t_cut_cmd	*ft_ls(char *path, char *options)
{
	struct dirent	*de;
	DIR				*dr;
	char			*tmp;
	t_cut_cmd		*concat;

	(void)concat;
	if (path)
		dr = opendir(path);
	else
		dr = opendir(".");
	concat = NULL;
	while (dr != NULL && ft_readdir(&de, dr))
	{
		tmp = ft_strdup(de->d_name);
		if (!is_same(options, "-a") && tmp[0] == '.')
			continue ;
		else
			add_to_env(&concat, tmp, _UNASSIGNED);
		tmp = NULL;
	}
	if (dr)
		closedir(dr);
	return (concat);
}
