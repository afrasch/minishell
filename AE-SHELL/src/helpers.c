#include "../includes/minishell.h"

void	set_list_2start(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	/* while (frame->cn->prev != NULL)
		frame->cn = frame->cn->prev; */
}

void ft_print_stack(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		printf("New Chunk\n");
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			printf("%s\n", frame->cc->cn->content);
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}
