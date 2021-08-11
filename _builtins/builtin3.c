#include "../includes/libshell.h"

static int	swaping(t_msh **msh, t_cut_cmd *env, char *new, size_t len)
{
	while (env)
	{
		if (!ft_strncmp(new, (env)->elem, len))
		{
			gc("pause");
			(env)->elem = ft_strdup(new);
			gc("resume");
			env->TOKEN = _UNASSIGNED;
			return (SUCCESS);
		}
		(env) = (env)->n;
	}
	gc("pause");
	add_env(msh, new, 0);
	gc("resume");
	return (SUCCESS);
}

static void	swaping2(t_msh **msh, t_cut_cmd *env, char *new)
{
	int		match;
	size_t	len;

	match = 0;
	len = ft_strlen(new);
	while (env && !match)
	{
		if (!ft_strncmp(env->elem, new, len))
			match = 1;
		env = env->n;
	}
	if (!match)
	{
		gc("pause");
		add_env(msh, new, ENV_SOLO);
		gc("resume");
	}
}

int	swap_env(t_msh **msh, char *new)
{
	t_cut_cmd	*env;
	size_t		len;
	int			match;

	len = 0;
	match = 0;
	env = (*msh)->env->head;
	while (new[len] && !match)
	{
		if (new[len] == '=')
			match = 1;
		len++;
	}
	if (new[len])
		swaping(msh, env, new, len);
	else
	{
		swaping2(msh, env, new);
		return (SUCCESS);
	}
	return (ERROR);
}
