/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 21:07:43 by motoure           #+#    #+#             */
/*   Updated: 2019/11/09 12:23:27 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long i;
	unsigned char *casted_s1;
	unsigned char *casted_s2;

	casted_s1 = (unsigned char *)s1;
	casted_s2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (casted_s1[i] == casted_s2[i] && casted_s1[i]
			&& casted_s2[i] && i < n)
	{
		if (i + 1 == n)
			return (casted_s1[i] - casted_s2[i]);
		if (casted_s1[i] != casted_s2[i] && casted_s1[i] && casted_s2[i])
			return (casted_s1[i] - casted_s2[i]);
		i++;
	}
	return (casted_s1[i] - casted_s2[i]);
}
