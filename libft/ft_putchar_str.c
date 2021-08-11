/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 09:06:00 by motoure           #+#    #+#             */
/*   Updated: 2021/07/02 02:23:50 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_str(char **str, char c)
{
	int		c_index;
	char	*ptr;

	c_index = ft_strlen(*str);
	*str = ft_realloc(*str, ft_strlen(*str) + 2);
	ptr = *str;
	ptr[c_index] = c;
	ptr[c_index + 1] = '\0';
}
