#ifndef BUILTINS_H
# define BUILTINS_H

# include "../includes/libshell.h"

int		builtin_export(t_msh *msh, t_cut_cmd *cmd);

int		builtin_unset(t_msh *msh, t_cut_cmd *cmd);

int		builtin_exit(t_msh *msh, t_cut_cmd *cmd);

void	add_builtin(int (***f_p_builtin)(t_msh *msh,
				t_cut_cmd *cmd), void *addr, int size);

void	handle_builtins(t_msh *msh, t_cut_cmd *cmd);

int		builtin_echo_return_value(t_msh *msh, t_cut_cmd *cmd, int mode);

int		builtin_echo(t_msh *msh, t_cut_cmd *cmd);

int		builtin_cd(t_msh *msh, t_cut_cmd *cmd);

int		builtin_pwd(t_msh *msh, t_cut_cmd *cmd);

int		builtin_env(t_msh *msh, t_cut_cmd *cmd);

int		print_env(t_msh *msh, t_cut_cmd *target);

int		swap_env(t_msh **msh, char *new);

int		check_option(t_msh *msh, t_cut_cmd *cmd);

int		check_export(t_msh *msh, t_cut_cmd *cmd);

void	print_alpha_export(t_msh *msh, t_cut_cmd *cmd);

t_cut_cmd	*ft_ls(char *path, char *options);
#endif
