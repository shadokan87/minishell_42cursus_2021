/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:55:26 by motoure           #+#    #+#             */
/*   Updated: 2021/08/10 17:26:55 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# include "../includes/libshell.h"
# define ERROR_H


int		append_error(t_msh *msh, t_cut_cmd *cmd, char *msg, int ret);
void	write_error(t_msh *msh);
void	handler(int n);
void	ft_error(t_cut_cmd *cmd, char *str, int errornum);
#endif
