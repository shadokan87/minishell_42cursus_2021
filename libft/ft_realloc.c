/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 09:30:38 by motoure           #+#    #+#             */
/*   Updated: 2021/07/04 17:53:12 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*return_value;

	return_value = NULL;
	if (!ptr)
		return (gc_malloc(size));
	else if (size <= (unsigned long)ft_strlen((char *)ptr))
		return (ptr);
	else
	{
		if (!(return_value = gc_malloc(size)))
			return (0);
		ft_memsub((void **)&return_value, ptr, 0, -1);
		free(ptr);
	}
	return (return_value);
}
