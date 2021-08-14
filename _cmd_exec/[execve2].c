#include "../includes/libshell.h"

char	*chr_or_zero(char *str, char c)
{
	char *chr;

	chr = ft_strchr(str, c);
	if (!chr)
		return (str + ft_strlen(str));
	return (chr);
}

void	strreduce_range(char **str, char *end)
{
	(void)end;
	char *ptr;

	ptr = *str;
	ptr = ft_strrev(ptr);
	printf("$END[%c]", *end);
	while (&(*ptr) != end + 3)
		ptr++;
	ptr = ft_strrev(ptr);
	printf("[%s]", ptr);
	$BR
}

int	get_dollar_end(char *dollar)
{
	int i;

	i = 1;
	while ((dollar[i]))
	{
		if (dollar[i] == '$')
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

void	_place_holder_handle_expand_env(t_msh *msh, t_cut_cmd *cmd)
{
	t_cut_cmd	*iterator;
	char		*current_write;
	char		*dollar;
	char		*found;
	int			i;
	(void)msh;

	i = 0;
	current_write = NULL;
	dollar = NULL;
	iterator = cmd->p;
	while (*iterator->elem)
	{
		if (*iterator->elem == '$')
		{
			dollar = ft_strtrim(ft_strndup(iterator->elem, get_dollar_end(iterator->elem)), "$");
			iterator->elem += get_dollar_end(iterator->elem);
			found = get_val_from_var(get_env_of(msh->envp, dollar));
			if (current_write)
				current_write = ft_strjoin(current_write, found);
			else
				current_write = ft_strdup(found);
			printf("$ELEM[%s]\n$CURR[%s]", iterator->elem, current_write);
		}
		if (!(*iterator->elem == '$'))
		{
			p_putchar_str(&current_write, *iterator->elem);
			iterator->elem++;
		}
	}
	iterator->elem = current_write;
	current_write = NULL;
	printf("\n$FINAL[%s]\n", iterator->elem);
	$BR
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
