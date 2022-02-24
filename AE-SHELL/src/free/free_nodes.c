#include "minishell.h"

void	free_node(t_node *node)
{
	if (node->content)
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

void	free_env(t_frame *frame)
{
	t_var *var;
	t_var *tmp;

	var = frame->shell_env_start;
	while (var && var->next)
	{
		tmp = var->next;
		free_var_node(var);
		var = tmp;
	}
	free_var_node(var);
}

void	ft_free_2d(void ***to_free)
{
	int	i;

	if (to_free == NULL || *to_free == NULL)
		return ;
	i = 0;
	while ((*to_free)[i] != NULL)
	{
		free((*to_free)[i]);
		(*to_free)[i] = NULL;
		i++;
	}
	free(*to_free);
	*to_free = NULL;
}
