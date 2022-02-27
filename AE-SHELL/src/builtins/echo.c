/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:08:43 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:53:27 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_init(t_frame *frame)
{
	frame->cc->built_in = B_ECHO;
	frame->nl = OFF;
}

static void	echo_write(t_node *node, t_frame *frame)
{
	while (node->next)
	{
		node = node->next;
		write (frame->cc->out_fd, node->content, ft_strlen(node->content));
		if (node->next)
			write (frame->cc->out_fd, " ", 1);
	}
	if (frame->nl == OFF)
		write (frame->cc->out_fd, "\n", 1);
}

int	echo(t_frame *frame)
{
	t_node	*node;

	echo_init(frame);
	node = frame->cc->node_start;
	if (!node)
		return (1);
	if (!node->next || !node->next->content)
	{
		write (frame->cc->out_fd, "\n", 1);
		return (0);
	}
	while (node->next && ft_strcmp(node->next->content, "-n") == 0)
	{
		node = node->next;
		frame->nl = ON;
	}
	echo_write(node, frame);
	return (0);
}
