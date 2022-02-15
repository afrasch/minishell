#include "minishell.h"

void	free_node(t_node *node)
{
	free(node->content);
	free(node);
	node = NULL;
}

static void	free_var_node(t_var *var)
{
	if (var->con)
		free(var->con);
	if (var->name)
		free(var->name);
	free(var);
}

void	free_env(t_frame *frame)//TODO doppelpointer
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
