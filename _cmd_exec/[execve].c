#include "../includes/libshell.h"

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
		bak = NULL;
	}
	return (bak);
}
