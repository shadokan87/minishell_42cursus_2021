#include "../includes/libshell.h"

/* BECAREFULL TO CHANGE THE MALLOC TO GC OR CALLOC ! */
void	init_jobs(t_msh **msh)
{
	(*msh)->jobs = (t_job *)malloc(sizeof(t_job));
	if (!(*msh)->jobs)
		ft_error(*msh, NULL, "Cannot allocate memory\n", 0);
	(*msh)->jobs->reading_line = NULL;
	(*msh)->jobs->have_been_read = NULL;
	(*msh)->jobs->prompt_status = 0;
}

/*where is tmp node ? */
void	init_tools(t_msh *msh)
{
	msh->tools = gc_malloc(sizeof(t_tools));
	if (!msh->tools)
		exit (0);
	msh->tools->tmp_node = 0;
	msh->tools->b_stdout = 0;
	msh->tools->head = NULL;
	msh->tools->tail = NULL;
	msh->tools->fdin = 0;
	msh->tools->fdout = 1;
	msh->tools->tmpfd = 0;
	msh->tools->nbpipe = 0;
	msh->tools->nbredir = 0;
	msh->tools->istmp = 0;
	msh->tools->last_op = 0;
	msh->tools->status = 0;
	msh->tools->run_status = 1;
	msh->tools->tmp_status = 0;
	msh->tools->pipe[0] = 0;
	msh->tools->pipe[1] = 0;
	msh->tools->noforked_exit = 0;
	msh->tools->error_msg = NULL;
	msh->tools->marker = NULL;
	msh->envp = NULL;
}

/* BECAREFULL TO CHANGE THE MALLOC TO GC OR CALLOC ! */
void	init_env(t_msh *msh, char **envp)
{
	int		i;

	i = 0;
	msh->env = (t_env_list *)malloc(sizeof(t_env_list));
	msh->env->head = NULL;
	msh->env->tail = NULL;
	msh->env->sub = NULL;
	create_env_list(&msh, envp[i]);
	while (envp[++i])
		add_env(&msh, envp[i], 0);
}

/* BECAREFULL TO CHANGE THE MALLOC TO GC OR CALLOC ! */
void	init_msh(t_msh **msh, char **envp)
{
	t_cut_cmd	*ptr;

	*msh = (t_msh *)malloc(sizeof(t_msh));
	init_jobs(msh);
	init_tools(*msh);
	init_env(*msh, envp);
	ptr = get_env_of((*msh)->env->head, "PATH");
	(*msh)->path = ft_split(ft_split(ptr->elem, '=')[1], ':');
	if (!(*msh)->path)
	{
		printf("PATH INIT FAILED\n");
		$BR
	}
	(*msh)->envp = (*msh)->env->head;
	if (!(*msh)->envp)
	{
		printf("ENVP INIT FAILED\n");
		$BR
	}
}
