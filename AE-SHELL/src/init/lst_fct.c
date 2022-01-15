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


int	lstsize(t_node *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**list_to_arr(t_node *node_start)
{
	t_node	*tmp;
	char	**arr;
	int		i;
	int		lst_size;

	i = 0;
	lst_size = lstsize(node_start);
	arr = calloc(lst_size + 1, sizeof(char *));
	tmp = node_start;
	while (tmp != NULL)
	{
		arr[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
