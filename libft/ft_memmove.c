/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 20:26:37 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:13:30 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*cast_dst;
	unsigned char	*cast_src;

	i = 0;
	cast_src = (unsigned char *)src;
	cast_dst = (unsigned char *)dst;
	if (src == dst)
		return (dst);
	if (cast_dst > cast_src)
	{
		while (++i <= len)
			cast_dst[len - i] = cast_src[len - i];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
