#include "../../includes/libshell.h"

/*
** (line:  27, col:  25):	Ternaries are forbidden
** (line:  28, col:  26):	Ternaries are forbidden
** (line:  32, col:   1):	Function has more than 25 lines
 */
int	p_check_par(t_msh *msh, char *str)
{
	int	count;
	int	open;
	int	close;
	int	i;
	int	err;

	i = -1;
	open = 0;
	close = 0;
	err = 1;
	count = 0;
	while (str[++i] && err)
	{
		if (str[i] == '(' || str[i] == ')')
			count++;
		if (str[i] == ')')
			close++;
		if (close > open)
			err = 0;
		if (str[i] == '(')
			open++;
	}
	err = open != close ? 0 : err;
	err = count % 2 == 0 ? err : 0;
	if (!err)
		msh->tools->error_msg = ft_strdup("Unbalanced parenthesis.");
	return (err);
}
