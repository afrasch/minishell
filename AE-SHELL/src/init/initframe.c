#include "minishell.h"

void	init_frame(t_frame *frame)
{
	frame->chunk_start = NULL;
	frame->cc = NULL;
	frame->shell_env = NULL;
	frame->shell_env_start = NULL;
	frame->e_status = 0;
	frame->hd_list = NULL;
	frame->single_com = OFF;
	frame->pid = -9;
	frame->paths = NULL;
}

void	init_node(t_frame *frame)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->prev = NULL;
	node->next = NULL;
	frame->cc->cn = node;
	frame->cc->cn->quote_st = NO_Q;
	frame->cc->cn->word = NO_Q;
	frame->cc->node_start = frame->cc->cn;
	frame->cc->in_fd = 0;
}

void	init_chunk(t_frame *frame)
{
	t_chunk	*chunk;

	chunk = ft_calloc(1, sizeof(t_chunk));
	chunk->prev = NULL;
	chunk->next = NULL;
	frame->cc = chunk;
	frame->cc->in_fd = STDIN_FILENO;
	frame->cc->out_fd = STDOUT_FILENO;
	frame->chunk_start = frame->cc;
	frame->cc->hd_bool = OFF;
}
