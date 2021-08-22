
int	exec_command(char *commande)
{
	char **split_of_command;
	int status;
	pid_t pid;

	status = -1;
	split_of_command = ft_split(commande, ' ');

	//exec below
	pid = fork();
	if (pid == -1)
		return (ERROR);
	else if (pid == 0)
		execve(split_of_command, &split_of_command[0] ...);
	waitpid(banane, &status, 0);
}

int	main(int argc, char **argv)
{
	//exec_command(argv[1]);
	return (0);
}
