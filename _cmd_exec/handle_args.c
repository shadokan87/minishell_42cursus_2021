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

void	inc_ret(t_cut_cmd *cmd, int *ret)
{
	(void)cmd;
	if (cmd->TOKEN == WILD_CARD && cmd->tail_wild_card)
		*ret += list_len(cmd->tail_wild_card);
	else
		*ret += 1;
}

int	strdup_wildcard_or_elem(t_cut_cmd *tail, char ***args, int i)
{
	t_cut_cmd	*iterator;

	if (tail->TOKEN == WILD_CARD && tail->tail_wild_card)
	{
		iterator = tail->tail_wild_card;
		while (iterator)
		{	
			(*args)[i] = ft_strdup(iterator->elem);
			iterator = iterator->p;
			i++;
		}
		return (list_len(tail->tail_wild_card));
	}
	(*args)[i] = ft_strdup(tail->elem);
	return (1);
}

char			**handle_args2(t_cut_cmd *cmd)
{
	int			ret;
	int			i;
	t_cut_cmd	*tail;
	char 		**args;

	ret = 0;
	i = 0;
	tail = cmd;
	if (!cmd)
		return (NULL);
	while (cmd && (cmd->TOKEN == C_ENV || cmd->TOKEN == C_BUILTIN
	|| cmd->TOKEN == ARG || cmd->TOKEN == OPTION || cmd->TOKEN == WILD_CARD))
	{
		inc_ret(cmd, &ret);
		cmd = cmd->p;
	}
	args = ft_calloc((ret + 1), sizeof(char*) * (ret + 1));
	while (tail && (tail->TOKEN == C_ENV || tail->TOKEN == C_BUILTIN || tail->TOKEN == ARG || tail->TOKEN == OPTION || tail->TOKEN == WILD_CARD))
	{
		ret = strdup_wildcard_or_elem(tail, &args, i);
		tail = tail->p;
		i += ret;
	}
	args[i] = NULL;
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
