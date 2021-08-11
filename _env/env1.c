/*
void	init_envp(t_msh *msh, char **envp)
{
	int i;
	t_cut_cmd *ptr;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		add_to_env(&msh->envp, envp[i], _UNASSIGNED);
		i++;
	}
	ptr = get_env_of(msh->envp, "PATH");
	msh->path = ft_split(ft_split(ptr->elem, '=')[1], ':');
	(void)msh;
}
*/
#include "../includes/libshell.h"

int	is_empty_env(t_cut_cmd *env)
{
	if (!env || env == NULL)
		return (SUCCESS);
	return (ERROR);
}

int	create_env_list(t_msh **msh, char *content)
{
	t_cut_cmd	*new_block;

	if (is_empty_env((*msh)->env->head))
	{
		new_block = (t_cut_cmd *)malloc(sizeof(t_cut_cmd));
		if (!new_block)
			return (-1);
		new_block->elem = content;
		new_block->TOKEN = _UNASSIGNED;
		new_block->is_last = 0;
		new_block->p = NULL;
		new_block->n = NULL;
		(*msh)->env->head = new_block;
		(*msh)->env->tail = new_block;
		(*msh)->env->size = 1;
		return (SUCCESS);
	}
	return (ERROR);
}

void	insert_things(t_msh **msh, t_cut_cmd **env_lst, t_cut_cmd *new_block)
{
	t_cut_cmd	**tracer;
	t_cut_cmd	**go_to;
	char		*str;
	size_t		len;

	(void)go_to;
	tracer = env_lst;
	str = new_block->elem;
	len = ft_strlen(str);
	printf("[new block = %s]\n", new_block->elem);
	while ((*tracer) != NULL && (ft_strncmp((*tracer)->elem, str, len) < 1))
		(tracer) = &(*tracer)->n;
	if (*tracer)
	{
		new_block->p = (*tracer);
		new_block->n = (*tracer)->n;
		(*tracer)->n = new_block;
		(*tracer)->n->p = new_block;
	}
	else
	{
		new_block->p = (*msh)->env->tail;
		(*msh)->env->tail->n = new_block;
		(*msh)->env->tail = new_block;
	}
	(*msh)->env->size++;
}

int	add_env(t_msh **msh, char *content, int mode)
{
	t_cut_cmd	*new_block;

	new_block = (t_cut_cmd *)malloc(sizeof(t_cut_cmd));
	if (!new_block)
		return (-1);
	if (!(ft_strchr(content, '=') + 1))
		new_block->elem = ft_strjoin(content, "=\"\"");
	else
		new_block->elem = ft_strdup(content);
	new_block->n = NULL;
	new_block->p = (*msh)->env->tail;
	if (mode)
		new_block->TOKEN = ENV_SOLO;
	else
		new_block->TOKEN = _UNASSIGNED;
	(*msh)->env->tail->n = new_block;
	(*msh)->env->tail = new_block;
	(*msh)->env->size++;
	return (SUCCESS);
}

int	add_to_env(t_cut_cmd **target, char *elem, t_TOKEN TOKEN)
{
	t_cut_cmd	*ret;

	ret = fill(elem, TOKEN);
	if (!*target)
	{
		*target = ret;
		return (1);
	}
	ret->n = *target;
	(*target)->p = ret;
	*target = ret;
	return (1);
}

t_cut_cmd	*get_env_of(t_cut_cmd *target, char *to_find)
{
	t_cut_cmd	*ptr;
	char		*current_var;

	ptr = target;
	current_var = NULL;
	if (!ptr)
		return (NULL);
	while (ptr)
	{
		current_var = ft_split(ptr->elem, '=')[0];
		if (!ft_strncmp(current_var, to_find, ft_strlen(to_find)))
			return (ptr);
		ptr = ptr->n;
	}
	return (NULL);
}
