#include "../includes/minishell.h"

// void	reset_frame(t_frame *frame)
// {
// 	if (frame != NULL)
// 	{
// 		if (frame->cn != NULL)
// 			ft_clear_nodes(&frame->cn);
// 		/* Hier muss dann viel gefreet werden, bei leaks hier gucken */
// 	}
// }

void	free_nodes(t_node *node)
{
	free(node->content);
	free(node);
	node = NULL;
}