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

static int	check_newline_flag(char *str)
{
	int	i;

	if (str[0] != '-' || str[1] == '\0')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	echo(t_frame *frame)
{
	t_node	*node;

	frame->cc->built_in = B_ECHO;
	frame->nl = OFF;
	node = frame->cc->node_start;
	if (!node)
		return (1);
	if (!node->next || !node->next->content)
	{
		write (frame->cc->out_fd, "\n", 1);
		return (0);
	}
	while (node->next && check_newline_flag(node->next->content) == TRUE)
	{
		node = node->next;
		frame->nl = ON;
	}
	echo_write(node, frame);
	return (0);
}
