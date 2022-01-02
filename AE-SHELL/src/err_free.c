#include "../includes/minishell.h"

void	reset_frame(t_frame *frame)
{
	if (frame != NULL)
	{
		if (frame->current_node != NULL)
			ft_clear_nodes(&frame->current_node);
		/* Hier muss dann viel gefreet werden, bei leaks hier gucken */
	}
}