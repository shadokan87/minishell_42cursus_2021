/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 17:18:24 by motoure           #+#    #+#             */
/*   Updated: 2020/01/07 17:19:32 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		y;
	char	swap;

	swap = '0';
	i = 0;
	y = ft_strlen(str) - 1;
	while (i < y)
	{
		swap = str[i];
		str[i] = str[y];
		str[y] = swap;
		i++;
		y--;
	}
	return (str);
}
