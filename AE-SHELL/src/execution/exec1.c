#include "../includes/minishell.h"

int	ft_check_argv(t_frame *frame)
{
	if (access(frame->cc->cmd_arr[0], X_OK) == 0)
		printf("ACCESS\n");
	return (0);
}

void	ft_childprocess(t_frame *frame)
{
	int	check;

	check = ft_check_argv(frame);
}


int execute_function(t_frame *frame)
{
	int pid;

	if (frame->cc->cc_errno != 0)
		printf("ERROR"); //HIER MUSS ERROR FUNCTION HIN MIT DEM ERRNO
	//list_to_array(frame);
	pid = fork();
	if (pid < 0)
		return (ERROR);
	if (pid == 0)
	{
		dup2(frame->cc->in_fd, STDIN_FILENO);
		dup2(frame->cc->out_fd, STDOUT_FILENO);
		ft_childprocess(frame);
	}
	else
		//ft_mainprocess(frame);
	wait(NULL);
	close(frame->cc->out_fd);
	close(frame->cc->in_fd);
	return (0);
}