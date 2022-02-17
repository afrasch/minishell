#include "minishell.h"

int	set_in_fd(t_frame *frame)
{
	frame->cc->in_fd = open(frame->cc->cn->next->content, O_RDONLY, 0777);
	printf("check\n");
	if (frame->cc->in_fd < 0)
	{
		frame->e_status = 1;
		print_error(frame->cc->cn->next->content, NULL, NULL);
		return (ERROR);
	}
	return(0);
}

int	set_out_fd(t_frame *frame, char mode)
{
	if (mode == 's')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (mode == 'd')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_WRONLY|  O_APPEND | O_CREAT, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->e_status = 1;
		print_error(frame->cc->cn->next->content, NULL, NULL);
		return (ERROR);
	}
	return (0);
}

int	set_right_red(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->out_fd >= 3)
		close(frame->cc->out_fd);
	if (cn->type == S_REDIR_R)
	{
		if (set_out_fd(frame, 's') == ERROR)
			return (ERROR);
	}
	else if (cn->type == D_REDIR_R)
	{
		if (set_out_fd(frame, 'd') == ERROR)
			return (ERROR);
	}
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int set_left_red(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd >= 3)
		close(frame->cc->in_fd);
	set_in_fd(frame);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}
