/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:02:59 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 14:03:11 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_all_fd(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	while (frame->cc != NULL)
	{
		if (frame->cc->in_fd != STDIN_FILENO)
			close(frame->cc->in_fd);
		if (frame->cc->out_fd != STDOUT_FILENO)
			close(frame->cc->out_fd);
		frame->cc = frame->cc->next;
	}
}

void	remove_hd(t_frame *frame)
{
	if (unlink(frame->cc->hd_path) != 0)
		print_error(NULL, NULL, NULL);
}

void	interrupt_rmv_hd(t_frame *frame)
{
	t_hd_list	*node;
	t_hd_list	*tmp;

	node = frame->hd_list;
	while (node != NULL)
	{
		tmp = node;
		if (unlink(node->name_of_hd) == ERROR)
			print_error("heredoc", NULL, NULL);
		free(node->name_of_hd);
		node->name_of_hd = NULL;
		free(node);
		node = NULL;
		node = tmp->next;
	}
	frame->hd_list = NULL;
	close_all_fd(frame);
}
