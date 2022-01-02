#include "../includes/minishell.h"

void	init_frame(t_frame *frame)
{
	frame->current_node = NULL;
}

void	next_node(t_frame *frame)
{
	t_node	*next_node;

	next_node = ft_calloc(1, sizeof(t_node));
	next_node->prev = frame->current_node;
	next_node->next = NULL;
	next_node->content = NULL;
	frame->current_node->next = next_node;
	frame->current_node = next_node;
}