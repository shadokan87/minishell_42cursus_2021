#include "../includes/libshell.h"

static char	**heredoc2(t_msh *msh, t_cut_cmd *cmd, t_cut_cmd *tmp)
{
	char		**args;
	int			i;

	i = 0;
	while (tmp != NULL)
	{
		if (tmp != msh->tools->tmp_node && tmp->TOKEN != D_L_REDIR)
			i++;
		tmp = tmp->p;
	}
	args = (char **)malloc(sizeof(char *) * i + 1);
	i = -1;
	while (cmd != NULL)
	{
		if (cmd != msh->tools->tmp_node && cmd->TOKEN != D_L_REDIR)
			args[++i] = cmd->elem;
		cmd = cmd->p;
	}
	args[++i] = NULL;
	return (args);
}

char	**handle_heredoc(t_msh *msh, t_cut_cmd *cmd, int mode)
{
	t_cut_cmd	*tmp;
	char		**args;

	tmp = cmd;
	if (mode == ARGS)
	{	
		args = (char **)malloc(sizeof(char *) * 3);
		args[0] = ft_strdup(cmd->elem);
		args[1] = ft_strdup("./msh_heredoc.msh");
		args[2] = NULL;
		msh->tools->istmp = 0;
	}
	else
		args = heredoc2(msh, cmd, tmp);
	return (args);
}

int	choose_args(t_msh *msh)
{
	t_cut_cmd	*cmd;

	cmd = msh->tools->tmp_node;
	if (!msh->tools->istmp)
		return (NO_ARGS);
	else if (cmd->p && cmd->p->TOKEN == ARG)
		return (ARGS_BUT);
	else
		return (ARGS);
}

/*args = (char**)gc_malloc(sizeof(char*) * (ret + 1)); */
char	**handle_args2(t_cut_cmd *cmd)
{
	t_cut_cmd	*tail;
	char		**args;
	int			ret;
	int			i;

	tail = cmd;
	ret = 0;
	i = -1;
	while (cmd && (cmd->TOKEN == C_ENV || cmd->TOKEN == C_BUILTIN
			|| cmd->TOKEN == ARG || cmd->TOKEN == OPTION))
	{
		ret++;
		cmd = cmd->p;
	}
	args = (char **)ft_calloc((ret + 1), sizeof(char *) * (ret + 1));
	while (tail && (tail->TOKEN == C_ENV || tail->TOKEN == C_BUILTIN
			|| tail->TOKEN == ARG || tail->TOKEN == OPTION))
	{
		args[++i] = ft_strdup(tail->elem);
		tail = tail->p;
	}
	args[++i] = NULL;
	return (args);
}

char	**handle_args(t_msh *msh, t_cut_cmd *cmd)
{
	int		tmp_check;
	char	**args;

	if (!msh || !cmd)
		return (NULL);
	tmp_check = choose_args(msh);
	if (msh->tools->istmp && (tmp_check == ARGS || tmp_check == ARGS_BUT))
		args = handle_heredoc(msh, cmd, tmp_check);
	else
		args = handle_args2(cmd);
	return (args);
}
