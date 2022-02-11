#include "minishell.h"

int	unset(t_frame *frame)
{
	t_var	*var;
	t_node	*node;

	if (!frame->cc->node_start || !frame->shell_env_start)
		return (2);
	node = frame->cc->node_start;
	while (node->next)
	{
		var = frame->shell_env_start;
		node = node->next;
		while (var)
		{
			if (ft_strcmp(node->content, var->name) == 0)
			{
				delete_var_node(frame, var);
				break ;
			}
			var = var->next;
		}
	}
	return (0);
}
