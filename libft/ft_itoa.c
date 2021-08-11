/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 01:16:16 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:12:51 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int		count(int n)
{
	int count;

	count = 0;
	while (n)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*ret;
	int		negative;

	if (n == -2147483648 || n == 0)
		return (ft_strdup(n == 0 ? "0" : "-2147483648"));
	negative = n > 0 ? 0 : 1;
	(negative) ? (n = n * -1) : 0;
	i = 0;
	if (!(ret = gc_malloc(sizeof(char) * count(n) + ((negative) ? 2 : 1))))
		return (0);
	while (n)
	{
		ret[i] = n % 10 + 48;
		n /= 10;
		i++;
	}
	if ((negative))
	{
		ret[i] = '-';
		i++;
	}
	ret[i] = '\0';
	return (ft_strrev(ret));
}
