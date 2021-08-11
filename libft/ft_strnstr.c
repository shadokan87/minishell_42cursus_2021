/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:04:30 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:17:43 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#define S size_t

static unsigned int		ft_strlen(char *str)
{
	unsigned int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char					*ft_strstr(char *str, char *to_find, size_t len)
{
	unsigned long		i;
	unsigned int		y;

	i = 0;
	y = 0;
	if (to_find[y] == '\0')
		return (str);
	while (str[i] && i < len)
	{
		if (str[i] == to_find[y])
		{
			while (str[i] == to_find[y] && to_find[y] && i < len)
			{
				i++;
				y++;
			}
			if (y == (ft_strlen(to_find)))
				return (str + (i - y));
			else
				i--;
		}
		y = 0;
		i++;
	}
	return (NULL);
}

char					*ft_strnstr(const char *haystack,
		const char *needle, S len)
{
	char *return_value;

	return_value = ft_strstr((char *)haystack, (char *)needle, len);
	return (return_value);
}
