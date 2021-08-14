#include "../includes/libshell.h"

int	c_is_present(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*n_dup(char *str, int start, int end)
{
	char	*ret;

	ret = NULL;
	if (!start || !end || end - start > ft_strlen(str))
		return (ret);
	while (start < end)
	{
		p_putchar_str(&ret, str[start]);
		start++;
	}
	return (ret);
}

char	*str_modulo(char *src, char **modulo, int inc)
{
	char	*ret;
	char	*modulo_ptr;

	ret = NULL;
	modulo_ptr = *modulo;
	if (inc > ft_strlen(src))
	{
		modulo_ptr = NULL;
		*modulo = NULL;
		return (NULL);
	}
	ret = ft_strndup(src, inc);
	modulo_ptr = ret;
	*modulo = modulo_ptr;
	return (src + inc);
}

int	is_match(char *list, char sep, char *elem)
{
	int		i;
	char	**split;

	i = 0;
	if (!elem || !list)
		return (0);
	split = ft_split(list, sep);
	while (split[i])
	{
		if (!ft_strncmp(split[i], elem, ft_strlen(elem)))
			return (1);
		i++;
	}
	return (0);
}

int	is_match2(char *list, char sep, char *elem)
{
	int		i;
	char	**split;

	i = 0;
	if (!elem || !list)
		return (-1);
	split = ft_split(list, sep);
	while (split[i])
	{
		if (is_same(split[i], elem))
			return (i);
		i++;
	}
	return (-1);
}
