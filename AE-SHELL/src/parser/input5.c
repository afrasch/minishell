#include "../includes/minishell.h"

int	set_fd_here_doc(t_frame *frame)
{

	frame->cc->in_fd  = open("tmp_here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	return (0);
}

int	set_in_fd(t_frame *frame)
{

	frame->cc->in_fd = open(frame->cc->cn->next->content, O_RDONLY, 0777);
	return(0);
}

int	set_out_fd(t_frame *frame, char mode)
{
	if (mode == 's')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_CREAT | O_WRONLY, 0777);
	else if (mode == 'd')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_CREAT | O_APPEND, 0777);
	return (0);
}

int	set_here_docs(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd > 3)
		close(frame->cc->in_fd);
	set_fd_here_doc(frame);
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
			if (frame->cc->out_fd > 3)
				close(frame->cc->out_fd);
			if (cn->type == S_REDIR_R)
				set_out_fd(frame, 's');
			else if (cn->type == D_REDIR_R)
				set_out_fd(frame, 'd');
			delete_node(frame, frame->cc->cn);
			delete_node(frame, cn->next);
		}
		else if (cn->type == S_REDIR_L)
		{
			if (frame->cc->in_fd > 3)
				close(frame->cc->in_fd);
			set_in_fd(frame);
			delete_node(frame, frame->cc->cn);
			delete_node(frame, cn->next);
		}
		else if (frame->cc->cn->type == D_REDIR_L)
			set_here_docs(frame);
		else
			frame->cc->cn = frame->cc->cn->next;
	}
	return (0);
}

void prepare_pipe(t_frame *frame)
{
	int fd[2];

	if (frame->cc->next != NULL)
	{
		if (pipe(fd) < 0)
			printf("ERROR\n");
		frame->cc->out_fd = fd[1];
		frame->cc->next->in_fd = fd[0];
	}
}

int		handle_meta_arrows(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		prepare_pipe(frame);
		check_for_redir(frame);
		frame->cc = frame->cc->next;
	}
	return (0);
}
