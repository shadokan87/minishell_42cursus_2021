#include "../includes/libshell.h"

int	print_env(t_msh *msh, t_cut_cmd *target)
{
	(void)msh;
	if (!target)
	{
		printf("[ENV IS VOID]\n");
		return (0);
	}
	printf("/n**	PRINT LIST	**\n");
	while (target)
	{
		if (target->TOKEN != ENV_SOLO)
			printf("[%s]\n", target->elem);
		target = target->n;
	}
	return (1);
}
