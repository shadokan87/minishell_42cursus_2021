#include "../../includes/libshell.h"

void	free_mute(void)
{
	t_addr	*ptr;

	if (!g_gc->mute)
		return ;
	while (g_gc->mute)
	{
		ptr = g_gc->mute;
		free(ptr->g);
		free(ptr);
		g_gc->mute = g_gc->mute->n;
	}
	g_gc->mute = NULL;
}

void	free_normal(void)
{
	t_addr	*ptr;

	while (g_gc->normal)
	{
		ptr = g_gc->normal;
		free(ptr->g);
		free(ptr);
		g_gc->normal = g_gc->normal->n;
	}
	g_gc->normal = NULL;
}

int	collect(int mode)
{
	if (!g_gc)
		return (0);
	if (!mode || mode == 2)
		free_normal();
	if (mode || mode == 2)
		free_mute();
	if (mode == 2)
	{
		free(g_gc);
		g_gc = NULL;
	}
	return (1);
}

void	gc(char *instr)
{
	if (!g_gc)
		gc_init();
	if (!ft_strncmp(instr, "pause", ft_strlen(instr)))
		g_gc->dst = 1;
	else if (!ft_strncmp(instr, "resume", ft_strlen(instr)))
		g_gc->dst = 0;
	else if (!ft_strncmp(instr, "collect", ft_strlen(instr)))
		collect(0);
	else if (!ft_strncmp(instr, "collect -mute", ft_strlen(instr)))
		collect(1);
	else if (!ft_strncmp(instr, "collect -all", ft_strlen(instr)))
		collect(2);
	else
	{
		write(2, "GC_BAD_INSTR", 12);
		exit (0);
	}
}

int	push_to_mute(t_addr *new)
{
	if (!g_gc->mute)
	{
		g_gc->mute = new;
		return (1);
	}
	if (g_gc->dst)
	{
		new->n = g_gc->mute;
		g_gc->mute->p = new;
		g_gc->mute = new;
		return (1);
	}
	return (1);
}
