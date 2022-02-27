/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:01:22 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 14:02:12 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_frame_nodes(t_frame *frame)
{
	t_node	*cn;
	t_node	*tmp;

	tmp = frame->cc->node_start;
	while (tmp)
	{
		cn = tmp;
		tmp = cn->next;
		free_node(cn);
	}
}

static void	free_chunks_and_nodes(t_frame *frame)
{
	t_chunk	*tmp;

	frame->cc = frame->chunk_start;
	while (frame->cc != NULL)
	{
		free_frame_nodes(frame);
		ft_free_2d((void ***) &frame->cc->cmd_arr);
		if (frame->cc->hd_path != NULL)
		{
			free(frame->cc->hd_path);
			frame->cc->hd_path = NULL;
		}
		tmp = frame->cc->next;
		if (frame->cc)
		{
			free(frame->cc);
			frame->cc = NULL;
		}
		frame->cc = tmp;
	}
	frame->chunk_start = NULL;
}

static void	free_frame(t_frame *frame)
{
	t_hd_list	*tmp;

	ft_free_2d((void ***) &frame->paths);
	while (frame->hd_list != NULL)
	{
		tmp = frame->hd_list;
		if (frame->hd_list->name_of_hd != NULL)
		{
			free(frame->hd_list->name_of_hd);
			frame->hd_list->name_of_hd = NULL;
		}
		free(frame->hd_list);
		frame->hd_list = NULL;
		frame->hd_list = tmp->next;
	}
	frame->single_com = OFF;
}

void	reset_frame(t_frame *frame)
{
	free_chunks_and_nodes(frame);
	free_frame(frame);
}
