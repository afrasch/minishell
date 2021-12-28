#include "../includes/minishell.h"

void	init_frame(t_frame *frame)
{
	frame->current_node = NULL;
}

void	next_node(t_frame *frame)
{
	t_node *next_node;

	next_node = ft_calloc(1, sizeof(t_node));
	frame->current_node = next_node;
	frame->current_node->content = NULL;
}