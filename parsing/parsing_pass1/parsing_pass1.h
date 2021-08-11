#ifndef PARSING_PASS1_H
# define PARSING_PASS1_H

# include "../../includes/libshell.h"

int		p_str_to_struct(t_msh *msh, char *str);

int		p_process_line(t_msh *msh);

int		p_check_par(t_msh *msh, char *str);

int		p_quote_to_struct(t_msh *msh, char *str);

int		get_next_quote2(char *src, char **dst);

int		split_quotes(t_msh *msh, char *ptr);

int		p_check_quotes(t_msh *msh);

int		get_next_quote(char *str, int i);

int		is_builtin(char *str);

int		add_symbol(t_msh *msh, char *str, char *ret, int i);

int		p_check_symbols(t_msh *msh, char *str);

int		escape_symbol(t_msh *msh, char *str, char **ret, int i);

char	get_next_char(char *str, int i, char *regex);

char	find_quote(t_msh *msh, char quote, int remove);

char	*p_escape_line(t_msh *msh, char *str);

char	*p_near(char *str);

#endif