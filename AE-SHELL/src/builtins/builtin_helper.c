#include "../includes/minishell.h"

void	prepare_builtin_alone(t_frame *frame)
{
	frame->saved_in_fd = dup(STDIN_FILENO);
	frame->saved_out_fd = dup(STDOUT_FILENO);
	check_for_redir(frame);
	dup2(frame->cc->in_fd, STDIN_FILENO);
	dup2(frame->cc->out_fd, STDOUT_FILENO);
}



void	set_back_builtin_alone(t_frame *frame)
{
	close (frame->cc->in_fd);
	close (frame->cc->out_fd);
	dup2(frame->saved_in_fd, STDIN_FILENO) ;
	dup2(frame->saved_out_fd, STDOUT_FILENO);
	close(frame->saved_in_fd);
	close(frame->saved_out_fd);
}