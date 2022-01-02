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
