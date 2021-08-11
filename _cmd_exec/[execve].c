#include "../includes/libshell.h"

t_cut_cmd	*ft_ls(char *path, char *options)
{
	struct dirent	*de;
	DIR				*dr;
	char			*tmp;
	t_cut_cmd		*concat;

	(void)concat;
	if (path)
		dr = opendir(path);
	else
		dr = opendir(".");
	concat = NULL;
	while (dr != NULL && (de = readdir(dr)) != NULL)
	{
		tmp = ft_strdup(de->d_name);
		if (!is_same(options, "-a") && tmp[0] == '.')
			continue ;
		else
			add_to_env(&concat, tmp, _UNASSIGNED);
		tmp = NULL;
	}
	dr ? closedir(dr) : 0;
	return (concat);
}

char	*determine_path_type(t_cut_cmd *cmd, char *str)
{
	int		i;
	char	*modulo;

	(void)cmd;
	modulo = NULL;
	i = 0;
	if (!c_is_present(str, '/'))
		return (NULL);
	str = ft_strrev(str);
	while (str[i] != '/')
		i++;
	str = str_modulo(str, &cmd->elem, i);
	cmd->elem = ft_strrev(cmd->elem);
	return (ft_strrev(str));
}

void	ft_list_join(t_cut_cmd **left, t_cut_cmd *start, t_cut_cmd *right)
{
	t_cut_cmd	*iterator;

	(void)left;
	(void)start;
	(void)right;
	iterator = (*left);
	while ((iterator) && (iterator)->p
		&& (iterator->p) != start && (iterator) != start)
		(iterator) = (iterator)->p;
	(iterator)->p = right;
}

t_cut_cmd	**head_tail(t_msh *msh, char *mode)
{
	static t_cut_cmd	**bak;

	if (!bak)
	{
		gc("pause");
		bak = ft_calloc(2, sizeof(t_cut_cmd *) * 2);
		gc("resume");
	}
	if (is_same(mode, "backup") && !bak[0] && !bak[1])
	{
		bak[0] = msh->tools->head;
		bak[1] = msh->tools->tail;
		msh->tools->head = NULL;
		msh->tools->tail = NULL;
	}
	else if (is_same(mode, "restore"))
	{
		msh->tools->head = bak[0];
		msh->tools->tail = bak[1];
		gc_free(bak);
		bak = NULL;
	}
	return (bak);
}

// void			_place_holder_handle_wildcards(t_msh *msh, t_cut_cmd *cmd)
// {
// 	(void)cmd;
// 	(void)msh;
// 	t_cut_cmd *iterator;

// 	iterator = cmd;
// 	printf("ok %s", iterator->p->elem);
// 	$BR
// }
