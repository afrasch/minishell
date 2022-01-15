#include "../includes/minishell.h"

void	echo(t_frame *frame)
{
	t_node	*node;

	node = frame->cc->node_start;
	node = node->next;
	while (node->next != NULL)
	{
		write (frame->cc->out_fd, node->content, ft_strlen(node->content));
		write (frame->cc->out_fd, " ", 1);
		node = node->next;
	}
	write (frame->cc->out_fd, node->content, ft_strlen(node->content));
}

void	execute_builtin(t_frame *frame, char *cmd)
{
	if (check_for_builtin(cmd) == ECHO)
		echo(frame);
	// else if (check_for_builtin(cmd) == CD)
	// 	cd(frame);
	// else if (check_for_builtin(cmd) == PWD)
	// 	pwd(frame);
	// else if (check_for_builtin(cmd) == EXPORT)
	// 	export(frame);
	// else if (check_for_builtin(cmd) == UNSET)
	// 	unset(frame);
	// else if (check_for_builtin(cmd) == ENV)
	// 	env(frame);
	// else if (check_for_builtin(cmd) == EXIT)
	// 	exit(frame);
}
