/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:20:44 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:55:06 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	iter_var_del(t_var *var, t_node *node, t_frame *frame)
{
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

int	unset(t_frame *frame)
{
	t_var	*var;
	t_node	*node;
	int		re;

	re = 0;
	if (!frame->cc->node_start || !frame->shell_env_start)
		return (1);
	node = frame->cc->node_start;
	while (node->next)
	{
		var = frame->shell_env_start;
		node = node->next;
		if (is_valid_varname(node->content) == FALSE)
		{
			re = 1;
			print_error("unset", node->content, "not a valid identifier");
		}
		iter_var_del(var, node, frame);
	}
	return (re);
}
