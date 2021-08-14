#include "../includes/libshell.h"

char	*trim_left(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str == c)
		str++;
	return (str);
}

char	*trim_right(char *str, char c)
{
	return (ft_strrev(trim_left(ft_strrev(str), c)));
}

int	list_len(t_cut_cmd *list)
{
	int			i;
	t_cut_cmd	*iterator;

	i = 0;
	if (!list)
		return (0);
	iterator = list;
	while (iterator)
	{
		iterator = iterator->p;
		i++;
	}
	return (i);
}

static char	**keep_split_return_value(t_msh *msh, void	**start,
		char **current_write, t_TOKEN _TOKEN)
{
	*start = 0;
	if (*current_write)
		add(msh, *current_write, _TOKEN);
	*current_write = NULL;
	return (list_to_split(msh->tools->tail));
}

char	**keep_split(t_msh *msh, char *str, char sep, t_TOKEN _TOKEN)
{
	static void		*start;
	static char		*current_write;

	if (!start)
		start = &str[0];
	if (!*str)
		return (keep_split_return_value(msh, &start, &current_write, _TOKEN));
	if (*str == sep && &(*str) != start)
	{
		while (*str == sep)
		{
			p_putchar_str(&current_write, *str);
			str++;
		}
		add(msh, current_write, _TOKEN);
		current_write = NULL;
	}
	else
	{
		p_putchar_str(&current_write, *str);
		str++;
	}
	return (keep_split(msh, str, sep, _TOKEN));
}
