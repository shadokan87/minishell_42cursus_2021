#include "../../includes/libshell.h"

/*
** (line:  27, col:  25):	Ternaries are forbidden
** (line:  28, col:  26):	Ternaries are forbidden
** (line:  32, col:   1):	Function has more than 25 lines
 */
int	p_check_par(t_msh *msh, char *str)
{
	register int	count;
	register int	open;
	register int	close;
	register int	i;
	register int	err;

	i = -1;
	open = 0;
	close = 0;
	err = 1;
	count = 0;
	while (str[++i] && err)
	{
		count += (str[i] == '(' || str[i] == ')');
		close += (str[i] == ')');
		err = (close <= open);
		open += (str[i] == '(');
	}
	err = (open == close);
	err = (count % 2 == 0);
	return ((!err
	&& (msh->tools->error_msg = ft_strdup("Unbalanced parenthesis.")))
	|| err);
}
