#include "../includes/minishell.h"

void	ft_childprocess(t_frame *frame)
{
	frame->cc->cn = frame->cc->node_start;
	executer(frame, frame->cc->cn->content);
}


int execute_function(t_frame *frame)
{
	int pid;

	if (frame->cc->cc_errno != 0)
		printf("ERROR"); //HIER MUSS ERROR FUNCTION HIN MIT DEM ERRNO
	pid = fork();
	if (pid < 0)
		return (ERROR);
	if (pid == 0)
	{
		dup2(frame->cc->in_fd, STDIN_FILENO);
		dup2(frame->cc->out_fd, STDOUT_FILENO);
		ft_childprocess(frame);
	}
	// else
		//ft_mainprocess(frame);
	wait(NULL);
	/* if (frame->cc->out_fd != STDOUT_FILENO)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO)
		close(frame->cc->in_fd); */
	return (0);
}