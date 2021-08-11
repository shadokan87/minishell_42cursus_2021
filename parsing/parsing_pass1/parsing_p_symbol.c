#include "../../includes/libshell.h"

int	is_builtin(char *str)
{
	char	**list;
	int		i;

	i = 0;
	list = ft_split(BUILTIN_LIST, ' ');
	while (list[i])
	{
		if (!ft_strncmp(str, list[i], ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

/* 
** (line:  50, col:   1):	Function has more than 25 lines
*/
int	add_symbol(t_msh *msh, char *str, char *ret, int i)
{
	char	**split;
	char	*ptr;

	ptr = str + i + 1;
	split = ft_split(ptr, ' ');
	if (!split[0])
	{
		msh->tools->error_msg = p_near("endl");
		return (0);
	}
	if (is_symbol(split[0][0]))
	{
		if (((split[0][0] == '>' && str[i] == '>')
			|| (split[0][0] == '<' && str[i] == '<')
				|| (split[0][0] == '&' && str[i] == '&')
					|| (split[0][0] == '|' && str[i] == '|'))
						&& !is_symbol(split[0][1]))
		{
			if ((!split[0][1] && !split[1]))
			{
				msh->tools->error_msg = p_near("endl");
				return (0);
			}
			return (1);
		}
		msh->tools->error_msg = p_near(ret);
		return (0);
	}
	return (1);
}

int	p_check_symbols(t_msh *msh, char *str)
{
	int		i;
	int		ret2;
	char	*ret;

	i = 0;
	ret2 = -1;
	ret = NULL;
	while (str[i])
	{
		if (is_symbol(str[i]))
		{
			ret = ft_strndup(str + i, 1);
			if (!add_symbol(msh, str, ret, i))
				return (0);
			ret2 = 1;
		}
		i++;
	}
	return (ret2);
}

int	escape_symbol(t_msh *msh, char *str, char **ret, int i)
{
	(void)msh;
	p_putchar_str(ret, ' ');
	while ((is_symbol(str[i])) || (str[i] == '(') || (str[i] == '('))
	{		
		p_putchar_str(ret, str[i]);
		i++;
	}
	p_putchar_str(ret, ' ');
	return (i);
}
