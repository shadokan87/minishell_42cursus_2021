#include "../../includes/libshell.h"

void	gc_free_calloc(char **_calloc)
{
	int	i;

	i = -1;
	while (_calloc[++i])
		gc_free(_calloc[i]);
	gc_free(_calloc[i]);
	gc_free(_calloc);
}

void	gc_free(void *ptr)
{
	if (!free_mute_target(ptr))
		free_normal_target(ptr);
}

int	push_to_normal(t_addr *new)
{
	if (!g_gc->normal)
	{
		g_gc->normal = new;
		return (1);
	}
	if (g_gc->normal)
	{
		new->n = g_gc->normal;
		g_gc->normal->p = new;
		g_gc->normal = new;
		return (1);
	}
	return (1);
}

int	gc_push(void ***g)
{
	t_addr	*new;

	new = malloc(sizeof(t_addr));
	if (!new)
		return (0);
	new->g = g;
	new->n = NULL;
	new->p = NULL;
	if (g_gc->dst)
		return (push_to_mute(new));
	else
		return (push_to_normal(new));
	return (1);
}
