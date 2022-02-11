#include "minishell.h"

void	delete_node(t_frame	*frame, t_node *node)
{
	if (node->prev == NULL)
	{
		if (node->next != NULL)
		{
			node->next->prev = NULL;
			frame->cc->node_start = node->next;
			frame->cc->cn = node->next;
		}
		else
			frame->cc->node_start = NULL;
	}
	else
	{
		if (node->next == NULL)
		{
			node->prev->next = NULL;
			frame->cc->cn = node->next;
		}
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			frame->cc->cn = node->next;
		}
	}
	free_node(node);
}

void	delete_var_node(t_frame	*frame, t_var *node)
{
	t_var	*tmp;

	if (!node || !frame->shell_env_start)
		return ;
	tmp = frame->shell_env_start;
	if (tmp == node)
	{
		frame->shell_env_start = frame->shell_env_start->next;
		free(tmp->name);
		if (tmp->con)
			free(tmp->con);
		free(tmp);
		return ;
	}
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free(node->name);
	if (node->con)
		free(node->con);
	free(node);
}
