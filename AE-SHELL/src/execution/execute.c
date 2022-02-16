#include "minishell.h"

int prepare_pipe(t_exec *exec)
{
	if (pipe(exec->fd) < 0)
		// print_error(SHELLNAME, NULL, NULL, NULL);
		print_error(NULL, NULL, NULL);
	return (0);
}

static void executer(t_frame *frame, t_exec *exec)
{
	char	*lowletter_cmd;

	lowletter_cmd = NULL;
	if (frame->cc->node_start != NULL)
		lowletter_cmd = change_caps(frame->cc->node_start->content);
	if ((check_for_builtin(lowletter_cmd, frame) != NONE) && (frame->single_com == ON))
	{
		prepare_builtin_alone(frame);
		if (execute_builtin(frame, lowletter_cmd) != 0)
			print_error(frame->cc->node_start->content, NULL, "Builtin cannot be executed");
		set_back_builtin_alone(frame);
	}
	else
	{
		frame->pid = ft_fork();
		signal(SIGINT, child_killer);
		signal(SIGQUIT, child_killer);
		if (frame->pid == 0)
		{
			free(lowletter_cmd);
			ft_childprocess(frame, exec);//TODO if == ERROR protec
		}
		else if (frame->single_com == OFF)
			ft_parent(frame, exec, frame->cc);
	}
	free(lowletter_cmd);
}

int		execute_chunks(t_frame *frame)
{
	t_exec	exec;

	init_exec(&exec); // TODO free exec (ist nicht in frame!) notwendig?
	set_list_2start(frame);
	if (frame->cc->next == NULL && frame->cc->prev == NULL)
		frame->single_com = ON;
	if (solve_heredocs(frame) < 0)
	{
		interrupt_rmv_hd(frame);
		return (ERROR);
	}
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		if (frame->cc->next != NULL)
			prepare_pipe(&exec);
		check_for_redir(frame);
		executer(frame, &exec);
		if (frame->cc->out_fd != STDOUT_FILENO)
			close(frame->cc->out_fd);
		if (frame->cc->in_fd != STDIN_FILENO)
			close(frame->cc->in_fd);
		frame->cc = frame->cc->next;
		/* if (frame->cc->hd_bool == ON)
			remove_hd(frame); */
	}
	close(exec.tmp_fd);
	wait_for_childs(frame);
	interrupt_rmv_hd(frame);
	return (0);
}
