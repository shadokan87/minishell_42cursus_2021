/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:46:47 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:07:09 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static void		*ft_memset(void *b, int c, size_t len)
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

void			ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
