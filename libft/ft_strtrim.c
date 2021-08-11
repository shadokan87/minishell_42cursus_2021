/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 21:53:40 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:14:31 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		check_set(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		len_trim(char *s1, const char *set)
{
	int i;
	int y;

	y = 0;
	i = 0;
	while (check_set(s1[i], set) && s1[i])
		i++;
	if (s1[i] == '\0')
		return (1);
	y = i;
	i = ft_strlen((char *)s1) - 1;
	while (check_set(s1[i], set))
		i--;
	return (i - y + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len;
	char	*s2;

	if (!s1 || !set)
		return (ft_strdup(""));
	s2 = (char*)s1;
	len = len_trim(s2, set);
	if (!(str = gc_malloc(sizeof(char) * len + 1)))
		return (0);
	while (check_set(*s2, set))
		s2++;
	ft_strlcpy(str, s2, len + 1);
	return (str);
}
