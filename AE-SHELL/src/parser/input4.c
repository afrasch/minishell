#include "../includes/minishell.h"

void	set_fd_here_doc(t_frame *frame)
{
	int	fd;

	fd = open("tmp_here_doc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	//fill_here_doc()
	if (fd < 0)
		printf("ERROR");
	frame->cc->in_fd = fd;
}


void	check_for_here_docs(t_frame *frame)
{
	while (frame->cc->cn != NULL)
	{
		if (ft_strncmp(frame->cc->cn->content, "<<", 2) == 0 && frame->cc->cn->word == NO_Q)
		{
			if (frame->cc->in_fd > 3)
				close(frame->cc->in_fd);
			set_fd_here_doc(frame);
		}
		frame->cc->cn = frame->cc->cn->next;
	}
}


void	handle_meta_arrows(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		check_for_here_docs(frame);
		frame->cc = frame->cc->next;
	}
}