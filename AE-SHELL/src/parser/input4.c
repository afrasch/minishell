#include "../includes/minishell.h"

int	check_redir(t_node *node)
{
	if (node->type == S_REDIR_L || node->type == S_REDIR_R || node->type == D_REDIR_L
		|| node->type == D_REDIR_R)
	{
		if (node->next != NULL)
			if (node->next->type != WORD)
				printf("ERROR\n"); 
		if (node->next == NULL)
			printf("ERROR\n");
	}
	return (0);
}

int	check_end_quotes(t_node *node)
{
	if (node->quote_st != NO_Q)
		printf("ERROR QUOTES\n");
	return (0);
}

int	control_node(t_node *node)
{
	check_redir(node);
	check_end_quotes(node);
	return (0);
}

int	check_pipes(t_frame	*frame)
{
	t_chunk	*cc;

	cc = frame->cc;
	if (cc->prev != NULL && cc->prev->node_start == NULL
		&& cc->prev->expanded == OFF)
	{
		printf("ERROR PIPE\n");
		(void)frame;
		return (ERROR);
	}
	if (cc->next != NULL && cc->next->node_start == NULL
		&& cc->next->expanded == OFF)
	{
		printf("ERROR PIPE\n");
		(void)frame;
		return (ERROR);
	}
	return (0);
}

int control_chunk(t_frame* frame)
{
	check_pipes(frame);
	return (0);
}

int control_nodes_raw(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		control_chunk(frame);
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (control_node(frame->cc->cn) < 0)
				return (ERROR);
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	return (0);
}
