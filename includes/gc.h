#ifndef GC_H
# define GC_H

# include "./libshell.h"

typedef struct s_addr
{
	void							*g;
	int								immune;
	struct s_addr					*n;
	struct s_addr					*p;
}									t_addr;

typedef struct s_garbage_collector
{
	void							*to_ignore;
	int								dst;
	t_addr							*normal;
	t_addr							*mute;
}									t_gc;

extern t_gc	*g_gc;

void	gc(char *instr);

void	free_normal(void);

void	free_mute(void);

void	gc_init(void);

void	*gc_malloc(size_t size);

void	gc_free(void *ptr);

void	gc_free(void *ptr);

void	gc_free_calloc(char **_calloc);

void	*to_gc(void *ptr, void *ptr2);

void	gc(char *instr);

int		free_mute_target(void *target);

int		gcpush(void ***g);

int		free_normal_target(void *target);

int		collect(int mode);

int		push_to_mute(t_addr *new);

int		gc_push(void ***g);

int		push_to_normal(t_addr *new);

#endif
