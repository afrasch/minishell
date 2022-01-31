#include "../includes/minishell.h"

void	init_frame(t_frame *frame)
{
	frame->cc = NULL;
	frame->shell_env = NULL;
	frame->shell_env_start = NULL;
	frame->e_status = 44;
}

void	next_node(t_frame *frame)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->prev = frame->cc->cn;
	new_node->next = NULL;
	new_node->content = NULL;
	frame->cc->cn->next = new_node;
	frame->cc->cn = new_node;
	frame->cc->cn->quote_st = NO_Q;
	frame->cc->cn->word = NO_Q;
	frame->single_com = OFF;
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
	frame->cc->built_in = NONE;
	frame->cc->hd_bool = OFF;
}
