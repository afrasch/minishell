#include "minishell.h"

static void	close_all_fd(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	while (frame->cc != NULL)
	{
		if (frame->cc->in_fd != STDIN_FILENO)
			close(frame->cc->in_fd);
		if (frame->cc->out_fd != STDOUT_FILENO)
			close(frame->cc->out_fd);
		frame->cc = frame->cc->next;
	}
}

void	remove_hd(t_frame *frame)
{
	if (unlink(frame->cc->hd_path) != 0)
		print_error(NULL, NULL, NULL);
}

void	interrupt_rmv_hd(t_frame *frame)
{
	t_hd_list *node;
	t_hd_list *tmp;

	node = frame->hd_list;
	while (node!= NULL)
	{
		tmp = node;
		if (unlink(node->name_of_hd) < 0)//TODO protection
			print_error("heredoc", NULL, NULL);
		free(node->name_of_hd);
		node->name_of_hd = NULL;
		free(node);
		node = NULL;
		node = tmp->next;
	}
	frame->hd_list = NULL;
	close_all_fd(frame);
}
