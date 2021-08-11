#include "../../includes/libshell.h"

char	get_next_char(char *str, int i, char *regex)
{
	int	y;

	if (!str[i])
		return (0);
	while (str[i])
	{
		y = -1;
		while (regex[++y])
		{
			if (regex[0] == str[i])
				continue ;
			else
				return (str[i]);
		}
		i++;
	}
	return (0);
}

int	get_next_quote(char *str, int i)
{
	if (!str)
		return (-1);
	while (str[i] && str[i] != '\"' && str[i] != '\'')
		i++;
	if (!str[i])
		i = -1;
	return (i);
}
