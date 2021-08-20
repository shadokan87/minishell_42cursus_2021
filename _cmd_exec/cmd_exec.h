#include "../includes/libshell.h"

#ifndef CMD_EXEC_H
# define CMD_EXEC_H

# define NO_ARGS 0
# define ARGS 1
# define ARGS_BUT 2

void	simple_exec(t_msh *msh, t_cut_cmd *cmd);

void	cmd_nopipe(t_msh *msh, t_cut_cmd *cmd);

void	cmd_pipe(t_msh *msh, t_cut_cmd *cmd);

void	delete_heredoc(t_msh *msh);

void	son_fork(t_msh *msh, t_cut_cmd *cmd, int bfd);

void	father_fork(t_msh *msh, t_cut_cmd *cmd, int pid, int *bfd);

void	move_pos(t_msh *msh, t_cut_cmd **pos);

char	*_place_holder_get_path(t_msh *msh, t_cut_cmd *cmd);

char	*determine_path_type(t_cut_cmd *cmd, char *str);

char	**handle_heredoc(t_msh *msh, t_cut_cmd *cmd, int mode);

char	**handle_args(t_msh *msh, t_cut_cmd *cmd);

int		choose_args(t_msh *msh);

int		handle_cmd(t_msh *msh, t_cut_cmd *pos);

int		_placeholder_handle_cmd(t_msh *msh);

int		goto_next_div(t_msh *msh, t_cut_cmd **pos);

void	init_pos(t_cut_cmd *tail, t_cut_cmd **pos);

char	*get_val_from_var(t_cut_cmd *var);

t_TOKEN		scope_contain_redir(t_cut_cmd *pos);

t_cut_cmd	*get_next_token_scope(t_cut_cmd *pos, t_TOKEN TOKEN);

#endif
