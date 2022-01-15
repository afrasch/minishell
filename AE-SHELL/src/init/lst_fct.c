#include "../includes/minishell.h"

void	ft_clear_nodes(t_node **current_node)
{
	t_node	*node;

	while ((*current_node) != NULL)
	{
		node = (*current_node)->prev;
		free((*current_node));
		(*current_node) = NULL;
		(*current_node) = node;
	}
}


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

char	**list_to_arr(t_node *node_start)
{
	t_node	*tmp;
	char	**arr = NULL;
	int		i;

	i = 0;
	tmp = node_start;
	while (tmp != NULL)
	{
		arr[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	return (arr);
}
