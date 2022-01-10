#include "../includes/minishell.h"

void	reset_frame(t_frame *frame)
{
	if (frame != NULL)
	{
		if (frame->cc->cn != NULL)
			ft_clear_nodes(&frame->cc->cn);
		/* Hier muss dann viel gefreet werden, bei leaks hier gucken */
	}
}