#include "../../includes/libshell.h"

char	*p_escape_line(t_msh *msh, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if ((is_symbol(str[i])) || (str[i] == '(') || (str[i] == '('))
			i = escape_symbol(msh, str, &ret, i);
		p_putchar_str(&ret, str[i]);
		i++;
	}
	return (ret);
}

/* Function has more than 25 lines */
int	p_str_to_struct(t_msh *msh, char *str)
{
	register int		i;
	register int		y;
	register int		z;
	char	*new;
	char	**split;

	i = 0;
	y = -1;
	z = 0;
	split = NULL;
	new = NULL;
	if (!str)
		split = ft_split(msh->jobs->have_been_read, ' ');
	else if (*str != '\"' && *str != '\'')
		split = ft_split(str, ' ');
	if (str && (str[0] == '\'' || str[0] == '"'))
		return (p_quote_to_struct(msh, str));
	while (split[i])
	{
		while (split[i][z])
		{
			if ((split[i][z]) && (split[i][z] == '(' || split[i][z] == ')'))
			{
				if (new)
					add(msh, new, _UNASSIGNED);
				if (split[i][z] == '(')
					add(msh, "(", OPEN_DIV);
				else
					add(msh, ")", CLOSED_DIV);
				new = NULL;
			}
			else
				p_putchar_str(&new, split[i][z]);
			z++;
		}
		if (new)
		{
			add(msh, new, _UNASSIGNED);
			new = NULL;
		}
		i++;
		z = 0;
	}
	return (1);
}

int	p_process_line(t_msh *msh)
{
	if (!msh->jobs->have_been_read)
		return (0);
	if (!p_check_quotes(msh))
		return (0);
	if (!msh->tools->head)
	{
		if (!p_check_symbols(msh, msh->jobs->have_been_read)
			|| !p_check_par(msh, msh->jobs->have_been_read))
			return (0);
		msh->jobs->have_been_read
			= p_escape_line(msh, msh->jobs->have_been_read);
		p_str_to_struct(msh, NULL);
	}
	else
		p_p_check_par_join(msh);
	p_p_determine_token(msh);
	p_p_ready_to_process(msh);
	return ((msh->tools->error_msg == NULL));
}

char	*p_near(char *str)
{
	char	*ret;
	char	*ret2;

	if (!ft_strncmp(str, "endl", ft_strlen(str)))
		ret2 = ft_strdup("\\n");
	else
		ret2 = ft_strndup(str, 1);
	ret = ft_strjoin("parse error near '", ret2);
	ret = ft_strjoin(ret, "'");
	return (ret);
}
