#include "minishell.h"

static void	echo_init(t_frame *frame)
{
	frame->cc->built_in = B_ECHO;
	frame->nl = OFF;
}

int	echo(t_frame *frame)
{
	t_node	*node;

	echo_init(frame);
	node = frame->cc->node_start;
	if (!node)
		return (2);
	if (!node->next || !node->next->content)
	{
		write (frame->cc->out_fd, "\n", 1);
		return (0);
	}
	while (ft_strcmp(node->next->content, "-n") == 0)
	{
		node = node->next;
		if (!node->next)
			return (2);
		frame->nl = ON;
	}
	while (node->next)
	{
		node = node->next;
		write (frame->cc->out_fd, node->content, ft_strlen(node->content));
		if (node->next)
			write (frame->cc->out_fd, " ", 1);
	}
	if (frame->nl == OFF)
		write (frame->cc->out_fd, "\n", 1);
	return (0);
}
