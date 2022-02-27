/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_input_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:30:37 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 02:32:04 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_slashes(t_node *node, t_frame *frame)
{
	if (node == frame->cc->node_start)
	{
		if (node->content && ft_strncmp(node->content, "/", 1) == 0)
		{
			if (ft_strlen(node->content) == 1
				|| ft_strncmp(node->content, "//", 2) == 0)
			{
				frame->e_status = 126;
				return (print_error(node->content, NULL, "is a directory"));
			}
			else if (access(node->content, F_OK) == ERROR)
			{
				frame->e_status = 127;
				return (print_error(node->content, NULL, NULL));
			}
		}
	}
	return (0);
}

static int	check_redir(t_node *node, t_frame *frame)
{
	if (node->type == S_REDIR_L || node->type == S_REDIR_R
		|| node->type == D_REDIR_L
		|| node->type == D_REDIR_R)
	{
		if (node->next)
		{
			if ((node->type == D_REDIR_R && node->next->type != WORD)
				|| (node->type == D_REDIR_L && node->next->type == D_REDIR_L)
				|| (node->type == D_REDIR_L && node->next->type == S_REDIR_R))
			{
				frame->e_status = 258;
				return (print_error(node->next->content, NULL,
						"syntax error near unexpected token"));
			}
		}
		else
		{
			frame->e_status = 258;
			return (print_error("newline", NULL,
					"syntax error near unexpected token"));
		}
	}
	return (0);
}

static int	check_end_quotes(t_node *node, t_frame *frame)
{
	if (node->quote_st == SINGLE_Q)
	{
		frame->e_status = 258;
		return (print_error("\'", NULL, "syntax error near single quotes"));
	}
	if (node->quote_st == DOUBLE_Q)
	{
		frame->e_status = 258;
		return (print_error("\"", NULL, "syntax error near double quotes"));
	}
	return (0);
}

int	control_node(t_node *node, t_frame *frame)
{
	if (check_redir(node, frame) == ERROR
		|| check_end_quotes(node, frame) == ERROR
		|| check_slashes(node, frame) == ERROR)
		return (ERROR);
	return (0);
}
