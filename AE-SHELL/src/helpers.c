#include "../includes/minishell.h"

void	set_list_2start(t_frame *frame)
{
	frame->cn = frame->node_start;
	/* while (frame->cn->prev != NULL)
		frame->cn = frame->cn->prev; */
}

void ft_print_stack(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cn->next != NULL)
	{
		printf("%s\n", frame->cn->content);
		frame->cn = frame->cn->next;
	}
	printf("%s\n", frame->cn->content);//prints without quotes
}
