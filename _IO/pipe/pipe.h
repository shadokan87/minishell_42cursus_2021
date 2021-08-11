#ifndef PIPE_H
# define PIPE_H

# include "../../includes/libshell.h"

void	ispipe(t_msh *msh);

void	whatpostions(t_msh *msh);

int		getnext_pipe(t_cut_cmd **cmd);

#endif