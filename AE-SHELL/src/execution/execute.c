/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:41:12 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 23:57:29 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_pipe(t_exec *exec)
{
	if (pipe(exec->fd) == ERROR)
		print_error(NULL, NULL, NULL);
	return (0);
}

static void	fork_and_exec(t_frame *frame, t_exec *exec, char *lowletter_cmd)
{
	frame->pid = ft_fork(frame);
	if (frame->single_com == ON)
		signal(SIGQUIT, child_killer);
	else
		signal(SIGQUIT, child_killer_one_cmd);
	signal(SIGINT, child_killer);
	if (frame->pid == 0)
		ft_childprocess(frame, exec, lowletter_cmd);
	else if (frame->single_com == OFF)
		ft_parent(frame, exec, frame->cc);
}

static void	executer(t_frame *frame, t_exec *exec)
{
	char	*lowletter_cmd;

	lowletter_cmd = NULL;
	if (frame->cc->node_start != NULL)
		lowletter_cmd = change_caps(frame->cc->node_start->content);
	if ((check_for_builtin(lowletter_cmd, frame) != NONE)
		&& (frame->single_com == ON))
	{
		if (frame->chunk_start->e_status_file != 1)
		{	
			prepare_builtin_alone(frame);
			if (execute_builtin(frame, lowletter_cmd) != 0)
				print_error(frame->cc->node_start->content, NULL,
					"Builtin cannot be executed");
			set_back_builtin_alone(frame);
		}
	}
	else
		fork_and_exec(frame, exec, lowletter_cmd);
	free(lowletter_cmd);
	lowletter_cmd = NULL;
}

static void	loop_through_chunks(t_frame	*frame, t_exec *exec)
{
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		if (frame->cc->next != NULL)
			prepare_pipe(exec);
		check_for_redir(frame);
		executer(frame, exec);
		if (frame->cc->out_fd != STDOUT_FILENO)
			close(frame->cc->out_fd);
		if (frame->cc->in_fd != STDIN_FILENO)
			close(frame->cc->in_fd);
		frame->cc = frame->cc->next;
	}
}

int	execute_chunks(t_frame *frame)
{
	t_exec	exec;

	init_exec(&exec);
	set_list_2start(frame);
	if (frame->cc->next == NULL && frame->cc->prev == NULL)
		frame->single_com = ON;
	if (solve_heredocs(frame) == ERROR)
	{
		interrupt_rmv_hd(frame);
		return (ERROR);
	}
	loop_through_chunks(frame, &exec);
	close(exec.tmp_fd);
	wait_for_childs(frame);
	interrupt_rmv_hd(frame);
	return (0);
}
