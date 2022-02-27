/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rearrange.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:45:57 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:25:34 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_next_node(t_node *node)
{
	t_node	*node_to_free;

	node_to_free = node->next;
	if (node->next->next != NULL)
	{
		node->next = node->next->next;
		node->next->prev = node;
	}
	else
		node->next = NULL;
	free_node (node_to_free);
}

void	fuse_arrows(t_frame *frame)
{
	while (frame->cc->cn != NULL)
	{
		if (!frame->cc->cn->content)
			return ;
		if ((frame->cc->cn->content[0] == '>' && frame->cc->cn->word == NO_Q
				&& frame->cc->cn->next != NULL)
			&& (frame->cc->cn->next->content[0] == '>'
				&& frame->cc->cn->next->word == NO_Q))
		{
			add_letter('>', frame);
			delete_next_node(frame->cc->cn);
		}
		if ((frame->cc->cn->content[0] == '<' && frame->cc->cn->quote_st == NO_Q
				&& frame->cc->cn->next != NULL)
			&& (frame->cc->cn->next->content[0] == '<'
				&& frame->cc->cn->next->word == NO_Q))
		{
			add_letter('<', frame);
			delete_next_node(frame->cc->cn);
		}
		tag_node(frame->cc->cn);
		frame->cc->cn = frame->cc->cn->next;
	}
}

void	re_arrange_list(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		fuse_arrows(frame);
		frame->cc->in_fd = STDIN_FILENO;
		frame->cc->out_fd = STDOUT_FILENO;
		frame->cc->built_in = NONE;
		frame->cc = frame->cc->next;
	}
}
