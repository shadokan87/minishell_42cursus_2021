/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:53:06 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:02:02 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned long	i_array_b;
	unsigned char	*a;

	i_array_b = 0;
	a = (unsigned char *)b;
	while (i_array_b < len)
	{
		a[i_array_b] = (unsigned char)c;
		i_array_b++;
	}
	b = a;
	return (b);
}
