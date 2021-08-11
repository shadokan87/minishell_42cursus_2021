#include "../includes/libshell.h"

int	builtin_export(t_msh *msh, t_cut_cmd *cmd)
{
	int			ret;
	t_cut_cmd	*env;
	char		**env_split;
	char		*to_print;

	env = msh->env->head;
	if (cmd->p)
		if ((check_option(msh, cmd) == ERROR) || (check_export(msh, cmd) == ERROR))
			return (ERROR);
	if ((!cmd->p) || ((cmd->p)
			&& (cmd->p->TOKEN >= PIPE && cmd->p->TOKEN <= D_L_REDIR)))
	{
		if (!msh->tools->fdout)
			msh->tools->fdout = 1;
		while (env)
		{
			if (ft_strchr(env->elem, '='))
			{
				env_split = ft_split(env->elem, '=');
				to_print = ft_strjoin("declare -x ", env_split[0]);
				to_print = ft_strjoin(to_print, "=\"");
				to_print = ft_strjoin(to_print, env_split[1]);
				to_print = ft_strjoin(to_print, "\"");
				// ft_putstr_fd("declare -x", msh->tools->fdout);
				ft_putendl_fd(to_print, msh->tools->fdout);
			}
			else
			{
				ft_putstr_fd("declare -x ", 2);
				ft_putendl_fd(env->elem, 2);
			}
			env = env->n;
		}
		return (SUCCESS);
	}
	cmd = cmd->p;
	while (cmd && cmd->TOKEN != PIPE)
	{
		if (cmd->TOKEN == ARG)
			ret = swap_env(&msh, cmd->elem);
		cmd = cmd->p;
	}
	return (SUCCESS);
}

int	builtin_unset(t_msh *msh, t_cut_cmd *cmd)
{
	(void)msh;
	(void)cmd;
	if (!(cmd->p && cmd->p->TOKEN == ARG))
		return ((msh->tools->status = 0));
	return (2);
}

int	builtin_exit(t_msh *msh, t_cut_cmd *cmd)
{
	(void)msh;
	(void)cmd;
	// gc("collect -all");
	exit (0);
	return (2);
}

void	add_builtin(int (***f_p_builtin)(t_msh *msh, t_cut_cmd *cmd),
		void *addr, int size)
{
	static int	pos;
	char		*add_fail;

	add_fail = ft_strdup("BUILTIN_ARRAY_OVERFLOW, exiting now\n");
	(void)f_p_builtin;
	if (pos == size)
	{
		write(2, add_fail, ft_strlen(add_fail));
		gc("collect -all");
		exit (0);
	}
	(*f_p_builtin)[pos] = addr;
	pos++;
}

void	handle_builtins(t_msh *msh, t_cut_cmd *cmd)
{
	static	int	(**f_p_builtin)(t_msh *msh, t_cut_cmd *cmd);
	int			(*malloc_size)(t_msh *msh, t_cut_cmd *cmd);
	int			size;
	int			index_of_cmd;

	size = split_len(ft_split(BUILTIN_LIST, ' '));
	if (!f_p_builtin)
	{
		gc("pause");
		f_p_builtin = ft_calloc(size, sizeof(malloc_size) * size);
		gc("resume");
		add_builtin(&f_p_builtin, builtin_echo, size);
		add_builtin(&f_p_builtin, builtin_cd, size);
		add_builtin(&f_p_builtin, builtin_pwd, size);
		add_builtin(&f_p_builtin, builtin_env, size);
		add_builtin(&f_p_builtin, builtin_export, size);
		add_builtin(&f_p_builtin, builtin_unset, size);
		add_builtin(&f_p_builtin, builtin_exit, size);
	}
	index_of_cmd = is_match2(BUILTIN_LIST, ' ', cmd->elem);
	f_p_builtin[index_of_cmd](msh, cmd);
	exit (0);
}
