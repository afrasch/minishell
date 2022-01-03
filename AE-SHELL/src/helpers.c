#include "../includes/minishell.h"

void	set_list_2start(t_frame *frame)
{
	frame->current_node = frame->node_start;
	/* while (frame->current_node->prev != NULL)
		frame->current_node = frame->current_node->prev; */
}

void ft_print_stack(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->current_node->next != NULL)
	{
		printf("%s\n", frame->current_node->content);
		frame->current_node = frame->current_node->next;
	}
	printf("%s\n", frame->current_node->content);
}
