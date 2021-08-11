#include "../../includes/libshell.h"

t_gc	*g_gc = NULL;

void	gc_init(void)
{
	g_gc = malloc(sizeof(t_gc));
	if (!g_gc)
		return ;
	g_gc->normal = NULL;
	g_gc->mute = NULL;
	g_gc->dst = 0;
}

int	free_normal_target(void *target)
{
	t_addr	*ptr;
	t_addr	*ptr2;

	if (!g_gc->normal)
		return (0);
	ptr = g_gc->normal;
	while (ptr)
	{
		if (ptr->n && ptr->n->g == target)
		{
			ptr2 = ptr->n;
			ptr->n = ptr2->n;
			free(ptr2->g);
			free(ptr2);
			return (1);
		}
		ptr = ptr->n;
	}
	return (0);
}

int	free_mute_target(void *target)
{
	t_addr	*ptr;
	t_addr	*ptr2;

	if (!g_gc->mute)
		return (0);
	ptr = g_gc->mute;
	while (ptr)
	{
		if (ptr->n && ptr->n->g == target)
		{
			ptr2 = ptr->n;
			ptr->n = ptr2->n;
			free(ptr2->g);
			free(ptr2);
			return (1);
		}
		ptr = ptr->n;
	}
	return (0);
}

void	*gc_malloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	gc_push(ret);
	return (ret);
}
