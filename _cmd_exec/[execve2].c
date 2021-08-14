#include "../includes/libshell.h"

int	get_dollar_end(char *dollar)
{
	int i;

	i = 1;
	while ((dollar[i]))
	{
		if (dollar[i] == '$' && !(dollar[i + 1] && dollar[i + 1] == '$'))
			return (i);
		else if (!ft_isalnum(dollar[i]) && dollar[i] != '_')
			break ;
		i++;
	}
	return (i);
}

char	*get_val_from_var(t_cut_cmd *var)
{
	char *try;

	if (var)
	{
		try = ft_strchr(var->elem, '=');
		if (*try == '=')
		{
			if (!(*try + 1))
				return (NULL);
			else
				return (ft_strdup(try + 1));
		}
	}
	return (NULL);
}

void	_dollar_handle_append_failure(t_msh *msh, t_cut_cmd *iterator, char **current_write, char **elem_ptr)
{
	(void)msh;
	(void)iterator;
	(void)current_write;
	(void)elem_ptr;

	if (!current_write)
		*elem_ptr = ft_strdup($EMPTY_STRING);
}

void	_dollar_append_if_valid(t_msh *msh, t_cut_cmd *iterator, char **current_write, char **elem_ptr)
{
	char	*found;
	char	*dollar;

	found = NULL;
	dollar = NULL;
	dollar = ft_strtrim(ft_strndup(iterator->elem, get_dollar_end(iterator->elem)), "$");
	*elem_ptr = iterator->elem + get_dollar_end(iterator->elem);
	found = get_val_from_var(get_env_of(msh->envp, dollar));
	if (!found)
		_dollar_handle_append_failure(msh, iterator, current_write, elem_ptr);
	else if (*current_write)
		*current_write = ft_strjoin(*current_write, found);
	else
		*current_write = ft_strdup(found);
}

void	_place_holder_handle_expand_env(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*iterator;
	char		*current_write;
	int			i;
	(void)msh;

	i = 0;
	current_write = NULL;
	iterator = cmd;
	while (iterator)
	{
		while (*iterator->elem)
		{
			if (*iterator->elem == '$')
				_dollar_append_if_valid(msh, iterator, &current_write, &iterator->elem);
			if (!(*iterator->elem == '$'))
			{
				p_putchar_str(&current_write, *iterator->elem);
				iterator->elem++;
			}
		}
		iterator->elem = current_write;
		current_write = NULL;
		iterator = iterator->p;
	}
}

char	*_place_holder_get_path(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*update_path;
	char		**tmp;
	char		*tmp2;

	(void)tmp;
	update_path = get_env_of(msh->envp, "PATH");
	gc_free_calloc(msh->path);
	msh->path = ft_split(ft_split(update_path->elem, '=')[1], ':');
	tmp2 = determine_path_type(cmd, ft_strdup(cmd->elem));
	if (tmp2)
	{
		tmp = ft_calloc(2, sizeof(char *) * 2);
		tmp[0] = tmp2;
		return (get_path(cmd, tmp));
	}	
	else
		return (get_path(cmd, msh->path));
}

void	delete_heredoc(t_msh *msh)
{
	t_cut_cmd	*to_delete;
	char		**delete_args;
	char		*to_delete_path;
	int			pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		to_delete = (t_cut_cmd *)malloc(sizeof(t_cut_cmd));
		to_delete->elem = ft_strdup("/bin/rm");
		to_delete_path = get_path(to_delete, list_to_split(msh->env->head));
		delete_args = ft_split("rm -rf ./msh_heredoc.msh", ' ');
		msh->tools->marker = NULL;
		execve(to_delete->elem, delete_args, list_to_split(msh->env->head));
		printf("[FORK FORK FAILED]\n");
	}
	else
		waitpid(pid2, &msh->tools->status, 0);
}

void	simple_exec(t_msh *msh, t_cut_cmd *cmd)
{
	int		pid;
	int		bfd;

	bfd = -1;
	pipe(msh->tools->pipe);
	if ((cmd->p && cmd->p->TOKEN == ARG) && is_same(cmd->elem, "export"))
		builtin_export(msh, cmd);
	else
	{
		_place_holder_handle_wildcards(msh, cmd);
		_place_holder_handle_expand_env(msh, cmd);
		pid = fork();
		if (pid == 0)
			son_fork(msh, cmd, bfd);
		else if (pid > 0)
			father_fork(msh, cmd, pid, &bfd);
	}
}
