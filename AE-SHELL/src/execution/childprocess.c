/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:35:29 by elenz             #+#    #+#             */
/*   Updated: 2022/02/25 00:23:36 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_for_child(t_frame *frame, t_exec *exec)
{
	if (frame->cc->in_fd == PIPEIN)
		dup2(exec->tmp_fd, STDIN_FILENO);
	else
		dup2(frame->cc->in_fd, STDIN_FILENO);
	if (frame->cc->out_fd == PIPEOUT)
		dup2(exec->fd[1], STDOUT_FILENO);
	else
		dup2(frame->cc->out_fd, STDOUT_FILENO);
	if (frame->cc->out_fd != STDOUT_FILENO && frame->cc->out_fd < 0)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO && frame->cc->in_fd < 0)
		close(frame->cc->in_fd);
	close(exec->fd[0]);
	close(exec->fd[1]);
	close(exec->tmp_fd);
}

int	ft_childprocess(t_frame *frame, t_exec *exec, char *str)
{
	int		i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_for_pipe(frame);
	get_path(frame);
	if (!frame->cc->node_start || frame->cc->e_status_file)
		error_exit(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	if (frame->single_com == ON && i != ERROR)
		execute_one_cmd(frame, exec);
	dup_for_child(frame, exec);
	if (check_for_builtin(str, frame) != NONE)
	{
		frame->cc->out_fd = STDOUT_FILENO;
		exit(execute_builtin(frame, str));
	}
	if (execute_cmd(frame, i,
			change_caps(frame->cc->node_start->content)) == ERROR)
		error_exit(frame);
	return (0);
}

void	wait_for_childs(t_frame *frame)
{
	int	status[2];

	status[E_STATUS] = 0;
	while (status[E_STATUS] != ERROR)
	{
		status[E_STATUS] = waitpid(-1, &status[STAT_LOC], 0);
		if (frame->pid == status[E_STATUS])
		{
			if (WIFEXITED(status[STAT_LOC]))
				frame->e_status = WEXITSTATUS(status[STAT_LOC]);
			if (WIFSIGNALED(status[STAT_LOC]))
			{
				WTERMSIG(status[STAT_LOC]);
				frame->e_status = 128 + WTERMSIG(status[STAT_LOC]);
			}
		}
	}
}
