/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_input_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:29:41 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 02:30:28 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipes(t_frame	*frame)
{
	t_chunk	*cc;

	cc = frame->cc;
	if ((cc->prev != NULL && cc->prev->node_start == NULL
			&& cc->prev->expanded == OFF) || (cc->next != NULL
			&& cc->next->node_start == NULL && cc->next->expanded == OFF))
	{
		frame->e_status = 258;
		return (print_error("|", NULL, "syntax error near unexpected token"));
	}
	return (0);
}

static int	control_chunk(t_frame *frame)
{
	if (check_pipes(frame) == ERROR)
		return (ERROR);
	return (0);
}

int	input_check(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		if (control_chunk(frame) == ERROR)
			return (ERROR);
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (control_node(frame->cc->cn, frame) == ERROR)
				return (ERROR);
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	return (0);
}
