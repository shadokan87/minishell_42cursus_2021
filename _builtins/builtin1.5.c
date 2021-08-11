# include "../includes/libshell.h"

int	check_option(t_msh *msh, t_cut_cmd *cmd)
{
	int		quote;
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	quote = 0;
	while (cmd)
	{
		if (cmd->TOKEN == D_QUOTE || cmd->TOKEN == S_QUOTE)
			quote = 1;
		if ((cmd->TOKEN == OPTION || cmd->TOKEN == S_QUOTE || cmd->TOKEN == D_QUOTE) && cmd->elem[quote] == '-')
		{
			msh->tools->noforked_exit = 1;
			tmp = ft_substr(cmd->elem, 0, 2);
			str = ft_strdup("bash: export: ");
			str = ft_strjoin(str, tmp);
			str = ft_strjoin(str, ": invalid option\nexport: usage: export [no option] [name[=value] ...]\n");
			ft_error(msh, cmd, str, 2);
			return (ERROR);
		}
		quote = 0;
		cmd = cmd->p;
	}
	return (SUCCESS);
}

int	check_export(t_msh *msh, t_cut_cmd *cmd)
{
	int		i;
	char	*error;
	char	*str;

	i = -1;
	error = NULL;
	str = NULL;
	while(cmd && (cmd->TOKEN != ARG && cmd->TOKEN != D_QUOTE && cmd->TOKEN != S_QUOTE))
	{
		if (cmd->TOKEN == D_L_REDIR || cmd->TOKEN == L_REDIR || cmd->TOKEN == R_REDIR)
			return (SUCCESS);
		cmd = cmd->p;
	}
	str = cmd->elem;
	while (str[++i] && str[i] != '=')
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
		{
			error = ft_strdup("Minishell: export: \'");
			error = ft_strjoin(error, str);
			error = ft_strjoin(error, "\': not a valid identifier\n");
			msh->tools->noforked_exit = 1;
			ft_error(msh, cmd, error, 1);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

