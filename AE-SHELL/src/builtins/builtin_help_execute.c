/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_help_execute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:55:37 by elenz             #+#    #+#             */
/*   Updated: 2022/02/25 00:30:21 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_builtin_alone(t_frame *frame)
{
	frame->saved_in_fd = dup(STDIN_FILENO);
	frame->saved_out_fd = dup(STDOUT_FILENO);
	check_for_redir(frame);
	dup2(frame->cc->in_fd, STDIN_FILENO);
	dup2(frame->cc->out_fd, STDOUT_FILENO);
}

void	set_back_builtin_alone(t_frame *frame)
{
	if (frame->cc->in_fd != STDIN_FILENO)
		close (frame->cc->in_fd);
	if (frame->cc->out_fd != STDOUT_FILENO)
		close (frame->cc->out_fd);
	dup2(frame->saved_in_fd, STDIN_FILENO);
	dup2(frame->saved_out_fd, STDOUT_FILENO);
	close(frame->saved_in_fd);
	close(frame->saved_out_fd);
}

int	execute_builtin(t_frame *frame, char *cmd)
{
	if (check_for_builtin(cmd, frame) == B_ECHO)
		frame->e_status = echo(frame);
	else if (check_for_builtin(cmd, frame) == CD)
		frame->e_status = cd(frame);
	else if (check_for_builtin(cmd, frame) == PWD)
		frame->e_status = pwd(frame);
	else if (check_for_builtin(cmd, frame) == EXPORT)
		frame->e_status = export(frame);
	else if (check_for_builtin(cmd, frame) == UNSET)
		frame->e_status = unset(frame);
	else if (check_for_builtin(cmd, frame) == ENV)
		frame->e_status = env(frame);
	else if (check_for_builtin(cmd, frame) == EXIT)
		exit_minishell(frame);
	return (frame->e_status);
}
