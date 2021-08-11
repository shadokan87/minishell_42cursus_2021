#include "../includes/libshell.h"

int	builtin_echo_return_value(t_msh *msh, t_cut_cmd *cmd, int mode)
{
	t_cut_cmd	*iter;
	int			printf_ret;

	iter = cmd;
	printf_ret = 0;
	if (mode)
	{
		while (iter && (iter->TOKEN == OPTION || iter->TOKEN == ARG
				|| iter->TOKEN == D_QUOTE || iter-> TOKEN == S_QUOTE))
		{
			if (iter->n->n->TOKEN != C_BUILTIN)
				printf(" ");
			printf_ret += printf("%s", iter->elem);
			iter = iter->p;
		}
		return ((msh->tools->status = printf_ret));
	}
	return ((msh->tools->status = 0));
}

int	builtin_echo(t_msh *msh, t_cut_cmd *cmd)
{
	if (cmd->p)
	{
		if (cmd->p->TOKEN == OPTION
			&& is_same(cmd->p->elem, "-n")
			&& (cmd->p->p
				&& (cmd->p->p->TOKEN == D_QUOTE
					|| cmd->p->p->TOKEN == S_QUOTE
					|| cmd->p->p->TOKEN == ARG
					||cmd->p->p->TOKEN == OPTION)))
			return (builtin_echo_return_value(msh, cmd->p->p, 1));
		else if ((cmd->p && (cmd->p->TOKEN == D_QUOTE
					||cmd->p->TOKEN == S_QUOTE
					|| cmd->p->TOKEN == ARG
					|| (cmd->p->TOKEN == OPTION
						&& !is_same(cmd->p->elem, "-n")))))
			return ((msh->tools->status = printf("%s\n", cmd->p->elem) == -1));
	}
	if (!(cmd->p && cmd->p->TOKEN == OPTION && is_same(cmd->p->elem, "-n")))
		printf("\n");
	return (1);
}

int	builtin_cd(t_msh *msh, t_cut_cmd *cmd)
{
	if ((!cmd->p) || !(cmd->p->TOKEN == ARG
			|| cmd->p->TOKEN == D_QUOTE || cmd->p->TOKEN == S_QUOTE
			|| cmd->p->TOKEN == OPTION))
	{
		msh->tools->error_msg = ft_strdup("usage: cd [path]");
		return ((msh->tools->status = 0));
	}
	return ((msh->tools->status = chdir((const char *)cmd->p->elem) == -1));
}

int	builtin_pwd(t_msh *msh, t_cut_cmd *cmd)
{
	char	*pwd;

	(void)cmd;
	pwd = get_cwd();
	msh->tools->status = 0;
	if (pwd)
		printf("%s\n", pwd);
	else
		msh->tools->status = 1;
	return (1);
}

int	builtin_env(t_msh *msh, t_cut_cmd *cmd)
{
	if (cmd->p && (cmd->p->TOKEN == ARG || cmd->p->TOKEN == OPTION))
		return ((msh->tools->status = 0));
	return (print_env(msh, msh->env->head));
}
