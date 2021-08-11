#ifndef INIT_H
# define INIT_H 

# include "../includes/libshell.h"

void	init_jobs(t_msh **msh);

void	init_tools(t_msh *msh);

void	init_msh(t_msh **msh, char **envp);

#endif