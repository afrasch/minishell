#include "../includes/minishell.h"

int	set_fd_here_doc(t_frame *frame)
{

	frame->cc->in_fd  = open("tmp_here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		return (ERROR);
	}
	return (0);
}

int	set_in_fd(t_frame *frame)
{

	frame->cc->in_fd = open(frame->cc->cn->next->content, O_RDONLY, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		return (ERROR);
	}
	return(0);
}

int	set_out_fd(t_frame *frame, char mode)
{
	if (mode == 's')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_CREAT | O_WRONLY, 0777);
	else if (mode == 'd')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_CREAT | O_APPEND, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		return (ERROR);
	}
	return (0);
}

int	set_here_docs(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd > 3)
		close(frame->cc->in_fd);
	if (set_fd_here_doc(frame) < 0)
		return (ERROR);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int	set_right_red(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->out_fd > 3)
		close(frame->cc->out_fd);
	if (cn->type == S_REDIR_R)
	{
		if (set_out_fd(frame, 's') < 0)
			return (ERROR);
	}
	else if (cn->type == D_REDIR_R)
	{
		if (set_out_fd(frame, 'd') < 0)
			return (ERROR);
	}
	debug_print(frame);

	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int set_left_red(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd > 3)
			close(frame->cc->in_fd);
	set_in_fd(frame);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int	check_for_redir(t_frame *frame)
{
	t_node	*cn;

	while (frame->cc->cn != NULL)
	{
		cn = frame->cc->cn;
		if (cn->type == S_REDIR_R || cn->type == D_REDIR_R)
		{
			if (set_right_red(frame) < 0)
				return (ERROR);
		}
		else if (cn->type == S_REDIR_L)
		{
			if (set_left_red(frame) < 0)
				return (ERROR);
		}
		else if (frame->cc->cn->type == D_REDIR_L)
		{
			if (set_here_docs(frame) < 0)
				return (ERROR);
		}
		else
			frame->cc->cn = frame->cc->cn->next;
	}
	return (0);
}

int prepare_pipe(t_frame *frame)
{
	int fd[2];

	if (frame->cc->next != NULL)
	{
		if (pipe(fd) < 0)
		{
			frame->cc->cc_errno = errno;
			return (ERROR);
		}
		frame->cc->out_fd = fd[1];
		frame->cc->next->in_fd = fd[0];
	}
	return (0);
}

int		handle_meta_arrows(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		if (prepare_pipe(frame) == ERROR)
			return (ERROR);
		check_for_redir(frame);
		execute_function(frame);
		frame->cc = frame->cc->next;
	}
	return (0);
}
