/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 21:10:59 by motoure           #+#    #+#             */
/*   Updated: 2021/08/09 21:15:44 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H
# include "../includes/libshell.h"

int			MATCH(char *s1, char *s2, char *mode);
t_cut_cmd	**MATCH_END_WITH(t_msh *msh, char *str);
t_cut_cmd	**MATCH_ALL(t_msh *msh, char *str);
t_cut_cmd	**MATCH_START_WITH(t_msh *msh, char *str);
t_cut_cmd	**MATCH_CONTAIN(t_msh *msh, char *str);

void		substitute_wildcards_multiple(t_msh *msh, t_cut_cmd **pos);
void		substitute_wildcards(t_msh *msh, t_cut_cmd **pos);
void		_place_holder_handle_wildcards(t_msh *msh, t_cut_cmd *cmd);
void		_place_holder_determine_wildcard_type(t_msh *msh,
				t_cut_cmd **iterator);

#endif
