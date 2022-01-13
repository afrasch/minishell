#include "../includes/minishell.h"

int	control_node(t_node *node)
{
	if (node->type == S_REDIR_L || node->type == S_REDIR_R || node->type == D_REDIR_L
		|| node->type == D_REDIR_R)
	{
		if (node->next != NULL)
			if (node->next->type != WORD)
				return (ERROR); 
		if (node->next == NULL)
			return (ERROR);
	}
	return (0);
}

int control_nodes_raw(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
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
