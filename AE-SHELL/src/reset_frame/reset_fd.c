#include "minishell.h"

void	reset_fd(t_frame *frame)
{
	dup2(frame->saved_in_fd, STDIN_FILENO);
	dup2(frame->saved_out_fd, STDOUT_FILENO);
}