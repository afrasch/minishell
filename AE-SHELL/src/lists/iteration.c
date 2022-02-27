/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iteration.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:31:03 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 23:21:39 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_node(t_frame *frame)
{
	t_node	*new_node;

	new_node = ft_calloc_mini(1, sizeof(t_node), frame);
	new_node->prev = frame->cc->cn;
	new_node->next = NULL;
	new_node->content = NULL;
	frame->cc->cn->next = new_node;
	frame->cc->cn = new_node;
	frame->cc->cn->quote_st = NO_Q;
	frame->cc->cn->word = NO_Q;
	frame->single_com = OFF;
}

void	next_chunk(t_frame *frame)
{
	t_chunk	*next_chunk;

	next_chunk = ft_calloc_mini(1, sizeof(t_chunk), frame);
	next_chunk->prev = frame->cc;
	next_chunk->next = NULL;
	frame->cc->next = next_chunk;
	frame->cc = next_chunk;
	frame->cc->quote_st = NO_Q;
	frame->cc->built_in = NONE;
	frame->cc->hd_bool = OFF;
	frame->cc->expanded = OFF;
}

void	set_list_2start(t_frame *frame)
{
	frame->cc = frame->chunk_start;
}
