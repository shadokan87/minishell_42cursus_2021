#include "../includes/libshell.h"

int	split_len(char **split)
{
	int i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

char		**list_to_split(t_cut_cmd *target)
{
	char	**ret;
	int		i;
	t_cut_cmd	*count;

	i = 0;
	count = target;
	while (count)
	{
		count = count->n;
		i++;
	}
	ret = gc_malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (target)
	{
		ret[i] = ft_strdup(target->elem);
		target = target->n;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

char			*get_path(t_cut_cmd *cmd, char **paths)
{
	int				i;
	char			*str;
	char			*tmp;
	DIR				*o_dir;
	struct dirent	*r_dir;

	i = -1;
	if (!cmd || !paths)
		return (NULL);
	while (paths[++i])
	{
		o_dir = opendir(paths[i]);
		if (o_dir != NULL)
		{
			while ((r_dir = readdir(o_dir)) != NULL)
			{
				if (r_dir && (!ft_strncmp(cmd->elem, r_dir->d_name, (size_t)ft_strlen(r_dir->d_name))))
				{
					tmp = ft_strjoin(paths[i], "/");
					str = ft_strjoin(tmp, cmd->elem);
					if (!str)
						return (NULL);
					return (str);
				}
			}
			if (o_dir)
				closedir(o_dir);
		}
	}
	return (NULL);
}
