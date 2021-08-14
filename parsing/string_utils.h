#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include "../includes/libshell.h"

void		get_line_info(t_cut_cmd *to_debug);

void		msh_debug(t_msh *msh, char *elem);

void		print_split(char **split, char *way);

void		p_putchar_str(char **str, char c);

void		print_list2(t_cut_cmd *ptr);

void		print_list(t_msh *msh);

char		*trim_right(char *str, char c);

char		*trim_left(char *str, char c);

int			is_symbol(char c);

int			is_quote(char c, char type);

int			add(t_msh *msh, char *elem, t_TOKEN TOKEN);

int			split_len(char **split);

int			is_match(char *list, char sep, char *elem);

int			is_match2(char *list, char sep, char *elem);

int			is_same(char *s1, char *s2);

int			get_c_index(char *str, char c);

int			get_line(t_msh *msh, char *str);

int			c_is_present(char *str, char c);

int			get_enum_len(void);

char		*debug_get_line_name(t_cut_cmd *to_print);

char		*get_cwd(void);

char		*get_prompt_of(t_msh *msh, char *cwd);

char		**list_to_split(t_cut_cmd *target);

char		*get_path(t_cut_cmd *cmd, char **paths);

char		*n_dup(char *str, int start, int end);

char		*str_modulo(char *src, char **modulo, int inc);

char		**keep_split(t_msh *msh, char *str, char sep, t_TOKEN _TOKEN);

int			list_len(t_cut_cmd *list);

t_cut_cmd	*fill(char *elem, t_TOKEN TOKEN);

#endif
