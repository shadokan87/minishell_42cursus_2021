/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 14:41:23 by motoure           #+#    #+#             */
/*   Updated: 2019/11/08 14:49:12 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned int	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	unsigned int i;
	unsigned int y;
	unsigned int len;
	unsigned int tlen;

	i = 0;
	y = 0;
	len = 0;
	tlen = 0;
	while (dst[i] && i < dstsize)
		i++;
	len = i;
	while (src[y])
		y++;
	tlen = i + y;
	y = 0;
	while (src[y] && (len + y) < dstsize - 1 && dstsize != 0)
	{
		dst[i] = src[y];
		i++;
		y++;
	}
	if (!(i == dstsize))
		dst[i] = '\0';
	return (tlen);
}
