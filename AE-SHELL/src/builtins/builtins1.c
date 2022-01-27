#include "../includes/minishell.h"

void	echo(t_frame *frame)
{
	t_node	*node;

	node = frame->cc->node_start;
	node = node->next;
	frame->nl = OFF;
	while (ft_strcmp(node->content, "-n") == 0)
	{
		node = node->next;
		frame->nl = ON;
	}
	while (node->next != NULL)
	{
		write (frame->cc->out_fd, node->content, ft_strlen(node->content));
		write (frame->cc->out_fd, " ", 1);
		node = node->next;
	}
	write (1, node->content, ft_strlen(node->content));
	if (frame->nl != ON)
		write (1, "\n", 1);
	frame->cc->built_in = B_ECHO;
}

void	cd(t_frame *frame)
{
	t_node *node;
	char	*current_path;

	node = frame->cc->node_start;
	node = node->next;
	current_path = get_env_var(frame, "HOME");
	if (node->content == NULL)
	{
		if (chdir(current_path) == ERROR)
			return ;
			// print_error();
	}
	if (chdir(node->content) == ERROR)
			return ;
		// print_error();
	update_env(frame, "PWD", node->content);
}

void	pwd(t_frame *frame)
{
	char	*current_path;

	current_path = NULL;
	// current_path = get_env_var(frame, "PWD");//OR getcwd
	current_path = ft_strdup(getcwd(NULL, 0));
	write(frame->cc->out_fd, current_path, ft_strlen(current_path));
	write (frame->cc->out_fd, "\n", 1);
}


void	execute_builtin(t_frame *frame, char *cmd)
{
	if (check_for_builtin(cmd, frame) == B_ECHO)
		echo(frame);
	else if (check_for_builtin(cmd, frame) == CD)
		cd(frame);
	else if (check_for_builtin(cmd, frame) == PWD)
		pwd(frame);
	// else if (check_for_builtin(cmd) == EXPORT)
	// 	export(frame);
	// else if (check_for_builtin(cmd) == UNSET)
	// 	unset(frame);
	// else if (check_for_builtin(cmd) == ENV)
	// 	env(frame);
	// else if (check_for_builtin(cmd) == EXIT)
	// 	exit(frame);
}
