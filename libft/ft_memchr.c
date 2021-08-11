/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 00:04:14 by motoure           #+#    #+#             */
/*   Updated: 2019/11/08 00:36:44 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned long			i;
	unsigned char			*casted_s;

	i = 0;
	casted_s = (unsigned char *)s;
	while (i < n)
	{
		if (casted_s[i] == (unsigned char)c)
			return (&casted_s[i]);
		i++;
	}
	return (NULL);
}
