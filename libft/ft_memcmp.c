/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 00:49:47 by motoure           #+#    #+#             */
/*   Updated: 2019/11/08 01:04:35 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s1_casted;
	unsigned char *s2_casted;
	unsigned long i;

	i = 0;
	s1_casted = (unsigned char *)s1;
	s2_casted = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (s1_casted[i] != s2_casted[i])
			return (s1_casted[i] - s2_casted[i]);
		i++;
	}
	return (0);
}
