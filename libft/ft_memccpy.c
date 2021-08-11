/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 19:32:35 by motoure           #+#    #+#             */
/*   Updated: 2020/01/07 17:46:39 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char				*casted_dst;
	unsigned char				*casted_src;

	casted_dst = (unsigned char *)dst;
	casted_src = (unsigned char *)src;
	while (n)
	{
		*casted_dst = *casted_src;
		if (*casted_src == (unsigned char)c)
			return (casted_dst + 1);
		casted_dst++;
		casted_src++;
		n--;
	}
	return (NULL);
}
