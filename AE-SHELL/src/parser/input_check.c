#include "minishell.h"

void	check_for_pipe(t_frame *frame)
{
	if (frame->cc->prev != NULL && frame->cc->in_fd < 3)
		frame->cc->in_fd = PIPEIN;
	if (frame->cc->next != NULL && frame->cc->out_fd < 3)
		frame->cc->out_fd = PIPEOUT;
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
		else if (cn->type == D_REDIR_L)
			set_hd_as_infd(frame);
		else
			frame->cc->cn = frame->cc->cn->next;
	}
	return (0);
}
