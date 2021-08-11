/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 01:23:45 by motoure           #+#    #+#             */
/*   Updated: 2020/01/07 01:23:55 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	n == -2147483648 ? write(fd, "-2147483648", 11) : 0;
	n == 0 ? write(fd, "0", 1) : 0;
	if (n == -2147483648)
		return ;
	if (n == 0)
		return ;
	n > 0 ? 0 : ft_putchar_fd('-', fd);
	n = (n > 0 ? n : n * -1);
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}
