/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deletion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:28:15 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 14:30:48 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	empty_prev(t_frame *frame, t_node *node)
{
	if (node->next != NULL)
	{
		node->next->prev = NULL;
		frame->cc->node_start = node->next;
		frame->cc->cn = node->next;
	}
	else
		frame->cc->node_start = NULL;
}

void	delete_node(t_frame	*frame, t_node *node)
{
	if (node->prev == NULL)
		empty_prev(frame, node);
	else
	{
		if (node->next == NULL)
		{
			node->prev->next = NULL;
			frame->cc->cn = node->next;
		}
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			frame->cc->cn = node->next;
		}
	}
	free_node(node);
}

void	delete_var_node(t_frame	*frame, t_var *node)
{
	t_var	*tmp;

	if (!node || !frame->shell_env_start)
		return ;
	tmp = frame->shell_env_start;
	if (tmp == node)
	{
		frame->shell_env_start = frame->shell_env_start->next;
		free(tmp->name);
		if (tmp->con)
			free(tmp->con);
		free(tmp);
		return ;
	}
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free(node->name);
	if (node->con)
		free(node->con);
	free(node);
}
