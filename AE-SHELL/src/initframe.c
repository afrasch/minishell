#include "../includes/minishell.h"

void	init_frame(t_frame *frame)
{
	frame->cc = NULL;
}

void	next_node(t_frame *frame)
{
	t_node	*next_node;

	next_node = ft_calloc(1, sizeof(t_node));
	next_node->prev = frame->cn;
	next_node->next = NULL;
	next_node->content = NULL;
	frame->cn->next = next_node;
	frame->cn = next_node;
	frame->cn->quote_st = NO_Q;
	frame->cn->general_st = NO_Q;
}

void	next_chunk(t_frame *frame)
{
	t_chunk	*next_chunk;

	next_chunk = ft_calloc(1, sizeof(t_chunk));
	next_chunk->prev = frame->cc;
	next_chunk->next = NULL;
	next_chunk->content = NULL;
	frame->cc->next = next_chunk;
	frame->cc = next_chunk;
	frame->cc->quote_st = NO_Q;
}
