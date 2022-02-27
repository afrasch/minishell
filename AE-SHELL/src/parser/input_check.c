/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:32:01 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 14:32:02 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_pipe(t_frame *frame)
{
	if (frame->cc->prev != NULL && frame->cc->in_fd < 3)
		frame->cc->in_fd = PIPEIN;
	if (frame->cc->next != NULL && frame->cc->out_fd < 3)
		frame->cc->out_fd = PIPEOUT;
}

int	check_spaces(char c)
{
	if (c == ' ' || c == '	' || c == '\n')
		return (1);
	return (0);
}

int	check_for_redir(t_frame *frame)
{
	t_node	*cn;

	while (frame->cc->cn != NULL)
	{
		cn = frame->cc->cn;
		if (cn->type == S_REDIR_R || cn->type == D_REDIR_R)
		{
			if (set_right_red(frame) == ERROR)
				break ;
		}
		else if (cn->type == S_REDIR_L)
		{
			if (set_left_red(frame) == ERROR)
				break ;
		}
		else if (cn->type == D_REDIR_L)
		{
			if (set_hd_as_infd(frame) == ERROR)
				break ;
		}
		else
			frame->cc->cn = frame->cc->cn->next;
	}
	return (0);
}
