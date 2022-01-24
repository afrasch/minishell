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
	write (1, node->content, ft_strlen(node->content));
	write (1, "\n", 1);
	frame->cc->build_in = B_ECHO;
}

void	execute_builtin(t_frame *frame, char *cmd)
{
	if (check_for_builtin(cmd, frame) == B_ECHO)
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
