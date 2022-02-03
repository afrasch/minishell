#include "../includes/minishell.h"

int	ft_fork()
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("Error \n");//TODO error
		//Error exit;
	}
	return (pid);
}

void	init_exec(t_exec *exec)
{
	exec->tmp_fd = dup(STDIN_FILENO);
	if (exec->tmp_fd < 0)
	{
		printf("ERROR\n");
		//TODO ERRORFUNCTION
	}
}