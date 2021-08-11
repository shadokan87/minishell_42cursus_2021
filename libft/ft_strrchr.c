/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:34:41 by motoure           #+#    #+#             */
/*   Updated: 2020/01/07 18:34:49 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *tmp;

	tmp = 0;
	while (*s)
	{
		if (*s == c)
			tmp = (char *)s;
		s++;
	}
	if (*s == c)
		tmp = (char *)s;
	return (tmp);
}
