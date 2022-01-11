#include "../includes/minishell.h"

void	init_frame(t_frame *frame)
{
	frame->cc = NULL;
	frame->shell_env = NULL;
	frame->shell_env_start = NULL;
	frame->exp_st = OFF;
	// frame->exp_st = ON;
}

void	next_node(t_frame *frame)
{
	t_node	*next_node;

	next_node = ft_calloc(1, sizeof(t_node));
	next_node->prev = frame->cc->cn;
	next_node->next = NULL;
	next_node->content = NULL;
	// printf("check %s pointer %p\n", __func__, next_node);
	frame->cc->cn->next = next_node;//segfault
	frame->cc->cn = next_node;
	frame->cc->cn->quote_st = NO_Q;
	frame->cc->cn->word = NO_Q;
}

void	next_chunk(t_frame *frame)
{
	t_chunk	*next_chunk;

	next_chunk = ft_calloc(1, sizeof(t_chunk));
	next_chunk->prev = frame->cc;
	next_chunk->next = NULL;
	frame->cc->next = next_chunk;
	frame->cc = next_chunk;
	frame->cc->quote_st = NO_Q;
}
