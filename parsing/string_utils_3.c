/*
void	print_list2(t_cut_cmd *ptr)
{
	while (ptr)
	{
		printf("%s ->n", ptr->elem);
		ptr = ptr->p;
	}
	printf("\n");
}

void	print_list(t_msh *msh)
{
	t_cut_cmd *ptr;

	ptr = msh->tools->head;
	while (ptr)
	{
		printf("%s ->n", ptr->elem);
		ptr = ptr->n;
	}
	printf("\n");
}
*/
#include "../includes/libshell.h"
	char const *debug_tok[ ] = {"_START",
	"_UNASSIGNED",
	"C_BUILTIN",
	"C_ENV",
	"LAST_CMD",
	"ARG",
	"OPTION",
	"S_QUOTE",
	"D_QUOTE",
	"WILD_CARD",
	"ENV_SOLO",
	"PIPE",
	"R_REDIR",
	"D_R_REDIR",
	"L_REDIR",
	"D_L_REDIR",
	"OR",
	"AND",
	"OPEN_DIV",
	"CLOSED_DIV",
	"_END",
};

int	get_enum_len(void)
{
	int	i;

	i = _START;
	while (i < _END)
		i++;
	return (i);
}

int		is_same(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i])
		return (0);
	return (1);
}

/*
** Unrecognized token line 80, col 14
*/
int		get_c_index(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	if (c == $ZERO)
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*debug_get_line_name(t_cut_cmd *to_print)
{
	char *ret;

	ret = NULL;
	t_cut_cmd *ptr;

	ptr = to_print;
	while (!(!ptr->p))
		ptr = ptr->p;
	while (ptr)
	{
		if (!ret)
			ret = ft_strdup(ptr->elem);
		else
			ret = ft_strjoin(ft_strjoin(ret, " "), ptr->elem);
		ptr = ptr->n;
	}
	return (ret);
}

char	*get_cwd()
{
	char	cwd[PATH_MAX];

	//cwd = gc_malloc(sizeof(char) * PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (NULL);
}

char	*get_prompt_of(t_msh *msh, char *cwd)
{
	char		*ret;
	char		*arrow;
	char		*home_path;
	t_cut_cmd	*home;
	int			i;

	i = 0;
	(void)arrow;
	home_path = NULL;
	home = get_env_of(msh->envp, "HOME");
	if (home)
		home_path = ft_split(home->elem, '=')[1];
	if (home && is_same(home_path, cwd))
		cwd = ft_strdup("/~");
	if (!cwd)
		cwd = get_val_from_var(get_env_of(msh->tools->tail, "PWD"));
	if (!cwd)
		cwd = ft_strdup("?");
	cwd = ft_strrev(cwd);
	if (is_same(cwd, "/"))
		ret = ft_strndup("/", 1);
	else
		ret = ft_strndup(cwd, get_c_index(cwd, '/'));
	if (ft_strlen(cwd) < ft_strlen(home_path) && !is_same(ret, "/") && !is_same(ret, "~"))
		ret = ft_strjoin(ret, "/");
	ret = ft_strrev(ret);
	ret = ft_strjoin("  ", ft_strjoin(ret, "  "));
	ret = ft_strjoin(ft_strjoin(ANSI_COLOR_SUCCESS, ret), ANSI_COLOR_RESET);
	return (ft_strjoin(ret, " "));
}

int	get_line(t_msh *msh, char *str)
{
	char *curr_path;

	if (str)
		curr_path = str;
	else
		curr_path = get_prompt_of(msh, get_cwd());
	if (msh->tools->status != 0)
		curr_path = ft_strjoin(ft_strjoin(curr_path, ft_strjoin(ft_strjoin(ANSI_COLOR_FAILURE, " X "), ANSI_COLOR_RESET)), " ");
	msh->jobs->reading_line = readline(curr_path);
	if (!msh->jobs->reading_line)
		handler(0);
	if (is_same(ft_strtrim(msh->jobs->reading_line, "\n"), ""))
	{
		msh->tools->status = 0;
		msh->jobs->reading_line = NULL;
		return (0);
	}
	else
	{
		msh->jobs->have_been_read = ft_strdup(msh->jobs->reading_line);
		add_history(msh->jobs->reading_line);
		ft_putstr_fd(ft_strjoin(msh->jobs->reading_line, "\n"), msh->tools->history_fd);
	}
	return (1);
}

void	get_line_info(t_cut_cmd *to_debug)
{
	int i;
	char *str;
	t_cut_cmd *ptr;

	i = -1;
	ptr = to_debug;
	printf("Line:%s\n\telem: %s\n\tTOKEN: %s", debug_get_line_name(ptr), ptr->elem, debug_tok[ptr->TOKEN]);
	printf("\n");
	int end;

	end = 0;
	while ((str = readline("next / prev > ")))
	{
		if ((!ft_strncmp("prev", str, 4) || !ft_strncmp("p", str, 1)) && ptr->n)
			ptr = ptr->n;
		else if ((!ft_strncmp("next", str, 4) || !ft_strncmp("n", str, 1)) && ptr->p)
			ptr = ptr->p;
		else if (!(ft_strncmp("exit", str, 4)))
			break ;
		if (ptr)
		{	
			printf("Line:%s\n\telem: %s\n\tTOKEN: %s", debug_get_line_name(ptr), ptr->elem, debug_tok[ptr->TOKEN]);
			printf("\n");
		}
		i = -1;
	}
}

void	msh_debug(t_msh *msh, char *elem)
{
	if (!ft_strncmp(ft_strtrim(elem, " "), "line", 4))
		get_line_info(msh->tools->tail);
}

void	print_split(char **split, char *way)
{
	int i;

	i = 0;
	if (is_same(way, "rev"))
	{
		while (split[i + 1])
			i++;
		while (i > -1)
		{
			ft_putstr_fd(ft_strjoin(split[i], "\n"), 1);
			i--;
		}
	}
	else
	{
		while (split[i])
		{
			ft_putstr_fd(ft_strjoin(split[i], "\n"), 1);
			i++;
		}
	}
}
