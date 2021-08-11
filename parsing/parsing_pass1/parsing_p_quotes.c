#include "../../includes/libshell.h"

int	p_quote_to_struct(t_msh *msh, char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	p_putchar_str(&tmp, str[0]);
	str = ft_strtrim(str, tmp);
	if (!ft_strncmp(str, "", 1))
		return (0);
	while (str[i])
	{
		if (str[i] != tmp[0])
			p_putchar_str(&tmp2, str[i]);
		i++;
	}
	if (tmp[0] == '\'')
		add(msh, tmp2, S_QUOTE);
	else
		add(msh, tmp2, D_QUOTE);
	return (1);
}

char	find_quote(t_msh *msh, char quote, int remove)
{
	t_cut_cmd	*ptr;
	int			i;

	i = 0;
	ptr = msh->tools->head;
	while (ptr)
	{
		while (ptr->elem[i])
		{
			if (ptr->elem[i] == quote)
			{
				if (i == 0 && remove)
					ptr->elem++;
				printf("ok\n");
				return (quote);
			}
			i++;
		}
		ptr = ptr->n;
		i = 0;
	}
	return (-1);
}

int	get_next_quote2(char *src, char **dst)
{
	int		start;
	int		end;
	char	*ret;

	start = get_next_quote(src, 0);
	if (start == -1)
		return (-1);
	end = get_next_quote(src, start + 1);
	while ((src[end] != src[start]))
		end++;
	if (src[end + 1] && src[end + 1] == src[start])
		end = get_next_quote(src, end + 2);
	ret = ft_strndup(src + start, end + 1);
	*dst = ret;
	return (end + 1);
}

/*
** (line: 115, col:   1):	Function has more than 25 lines
*/
int	split_quotes(t_msh *msh, char *ptr)
{
	int		start_end[2];
	char	*str;
	char	*str2;

	str = NULL;
	str2 = NULL;
	start_end[0] = 0;
	start_end[1] = 0;
	if (!ptr)
	{
		ptr = msh->jobs->have_been_read;
		ptr = str_modulo(ptr, &str, get_next_quote(ptr, 0));
		if (!(p_check_symbols(msh, str)))
			return (0);
		str = p_escape_line(msh, str);
		p_str_to_struct(msh, ft_strtrim(str, " "));
		return (split_quotes(msh, ptr));
	}
	ptr += get_next_quote2(ptr, &str);
	p_str_to_struct(msh, ft_strtrim(str, " "));
	if (get_next_quote(ptr, 0) != -1)
		ptr = str_modulo(ptr, &str2, get_next_quote(ptr, 0));
	if (str2 && ft_strncmp(ft_strtrim(str2, " "), "", 1))
	{
		if (!(p_check_symbols(msh, str2)))
			return (0);
		p_str_to_struct(msh, ft_strtrim(p_escape_line(msh, str2), " "));
	}
	if (*ptr)
	{
		if (get_next_quote(ft_strtrim(ptr, " "), 0) != -1)
			return (split_quotes(msh, ft_strtrim(ptr, " ")));
		if (!(p_check_symbols(msh, ptr)))
			return (0);
		ptr = p_escape_line(msh, ptr);
		p_str_to_struct(msh, ptr);
		return (1);
	}
	return (1);
}

int	p_check_quotes(t_msh *msh)
{
	int	i;
	int	mark_double;
	int	mark_single;

	i = 0;
	mark_double = 0;
	mark_single = 0;
	while (msh->jobs->have_been_read[i])
	{
		if (msh->jobs->have_been_read[i] == '\"')
			mark_double++;
		else if (msh->jobs->have_been_read[i] == '\'')
			mark_single++;
		i++;
	}
	if (mark_double % 2 != 0 || mark_single % 2 != 0)
	{
		msh->tools->error_msg = ft_strdup("dquote not supported");
		return (0);
	}
	if (mark_double || mark_single)
		return (split_quotes(msh, NULL));
	return (1);
}
