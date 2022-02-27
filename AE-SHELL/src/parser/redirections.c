/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:25:47 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:26:33 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_in_fd(t_frame *frame)
{
	frame->cc->in_fd = open(frame->cc->cn->next->content, O_RDONLY, 0644);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->e_status_file = 1;
		print_error(frame->cc->cn->next->content, NULL, NULL);
		return (ERROR);
	}
	return (0);
}

int	set_out_fd(t_frame *frame, char mode)
{
	if (mode == 's')
		frame->cc->out_fd = open(frame->cc->cn->next->content,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (mode == 'd')
		frame->cc->out_fd = open(frame->cc->cn->next->content,
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->e_status_file = 1;
		print_error(frame->cc->cn->next->content, NULL, NULL);
		return (ERROR);
	}
	return (0);
}

int	set_right_red(t_frame *frame)
{
	t_node	*cn;
	int		ret;

	ret = 0;
	cn = frame->cc->cn;
	if (frame->cc->out_fd >= 3)
		close(frame->cc->out_fd);
	if (cn->type == S_REDIR_R)
		ret = set_out_fd(frame, 's');
	else if (cn->type == D_REDIR_R)
		ret = set_out_fd(frame, 'd');
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (ret);
}

int	set_left_red(t_frame *frame)
{
	t_node	*cn;
	int		ret;

	ret = 0;
	cn = frame->cc->cn;
	if (frame->cc->in_fd >= 3)
		close(frame->cc->in_fd);
	ret = set_in_fd(frame);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (ret);
}
