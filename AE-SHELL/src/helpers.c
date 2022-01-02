#include "../includes/minishell.h"

void ft_print_stack(t_frame *frame)
{
	while (frame->current_node->prev != NULL)
		frame->current_node = frame->current_node->prev;
	while (frame->current_node->next != NULL)
	{
		printf("%s\n", frame->current_node->content);
		frame->current_node = frame->current_node->next;
	}
	printf("%s\n", frame->current_node->content);
}
