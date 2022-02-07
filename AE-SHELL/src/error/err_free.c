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
//TODO free env
void	free_node(t_node *node)
{
	free(node->content);
	free(node);
	node = NULL;
}

void	free_var_node(t_var *var)
{
	if (var->con)
		free(var->con);
	if (var->name)
		free(var->name);
	free(var);
	var = NULL;
}


void	free_env(t_frame *frame)//TODO leaks mit system funktion
{
	t_var *var;
	t_var *tmp;

	var = frame->shell_env_start;
	while (var && var->next)
	{
		tmp = var->next;
		free_var_node(var);
		var = tmp->next;
	}
}

int 	print_error(int err_no, char *cmd, char * arg, char *message)
{
	char *msg;

	msg = strerror(err_no);
	(void)arg;
	if (message == NULL && cmd != NULL && msg)
		printf("%s: %s: %s\n", SHELLNAME, cmd, msg);
	if (message == NULL && cmd == NULL && msg)
		printf("%s: %s\n", SHELLNAME, msg);
	if (ft_strcmp(message, "command not found") == 0)
	{
		printf("%s: %s: %s\n", SHELLNAME, cmd, message);
		exit (127);//TODO nur cmd not found
	}
	else if (ft_strcmp(message, "syntax error near unexpected token") == 0)
		printf("%s: %s `%s'\n", SHELLNAME, message, cmd);
	else if (ft_strcmp("syntax error near double quotes", message) == 0)
		printf("%s: %s: %s\n", SHELLNAME, message, cmd);
	else if (ft_strcmp("syntax error near single quotes", message) == 0)
		printf("%s: %s: %s\n", SHELLNAME, message, cmd);
	else if (ft_strcmp("is a directory", message) == 0)
		printf("%s: %s: %s\n", SHELLNAME, cmd, message);
	else if (ft_strcmp(msg, message) == 0)
		printf("%s: %s: %s\n", SHELLNAME, cmd, msg);
	return (ERROR);
}
