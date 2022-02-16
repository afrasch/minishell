#include "minishell.h"

static int	print_export(t_frame *frame)
{
	t_var *var;

	var = frame->shell_env_start;
	if (!var)
		return (2);
	while (var)
	{
		if (var->just_export == OFF && var->con)
			printf("declare -x %s=%s\n", var->name, var->con);
		else
			printf("declare -x %s\n", var->name);
		var = var->next;
	}
	return (0);
}

int	export(t_frame *frame)
{
	t_node	*node;
	char	*name;
	char	*content;
	int		del_i;

	node = frame->cc->node_start;
	if (!node)
		return (2);
	if (!node->next)
		return (print_export(frame));
	node = node->next;
	while (node)
	{
		del_i = ft_int_strchr(node->content, '=');
		if (del_i < 0)
			add_var_node(frame, node->content, NULL, ON);
		else
		{
			name = ft_substr(node->content, 0, del_i);
			content = ft_substr(node->content, del_i + 1, ft_strlen(node->content) - del_i);
			content = ft_quote(content);
			add_var_node(frame, name, content, OFF);
		}
		node = node->next;
	}
	return (0);
}
