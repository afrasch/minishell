#include "../includes/minishell.h"

void	execute_one_cmd(t_frame *frame, t_exec *exec)
{
	int	i;

	get_path(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	dup2(frame->cc->in_fd, STDIN_FILENO);
	dup2(frame->cc->out_fd, STDOUT_FILENO);
	if (frame->cc->out_fd != STDOUT_FILENO)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO)
		close(frame->cc->in_fd);
	(void) exec;
	execute_cmd(frame, i, change_caps(frame->cc->node_start->content));
}

void	ft_childprocess(t_frame *frame, t_exec *exec)
{
	int		i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	printf("fdout %d\n", frame->cc->out_fd);
	if (frame->single_com == ON)
		execute_one_cmd(frame, exec);
	check_for_pipe(frame);
	printf("fdout %d\n", frame->cc->out_fd);
	get_path(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	if (frame->cc->in_fd == PIPEIN)
		dup2(exec->tmp_fd, STDIN_FILENO);
	else
		dup2(frame->cc->in_fd, STDIN_FILENO);
	if (frame->cc->out_fd == PIPEOUT)
	{
		printf("geht rein\n");
		dup2(exec->fd[1], STDOUT_FILENO);
	}
	else
		dup2(frame->cc->out_fd, STDOUT_FILENO);
	if (frame->cc->out_fd != STDOUT_FILENO)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO)
		close(frame->cc->in_fd);
	close(exec->fd[0]);
	close(exec->fd[1]);
	close(exec->tmp_fd);
	execute_cmd(frame, i, change_caps(frame->cc->node_start->content));//executed
}

void	ft_parent(t_exec *exec, t_chunk *cc)
{
	close(exec->fd[1]);
	close(exec->tmp_fd);
	exec->tmp_fd = dup(exec->fd[0]);
	close(exec->fd[0]);
	//TODO free cc falls Fehler
	(void)cc;
}

int execute_function(t_frame *frame, t_exec *exec)
{
	int 	pid;
	char	*lowletter_cmd;

	lowletter_cmd = NULL;
	if (frame->cc->node_start != NULL)
		lowletter_cmd = change_caps(frame->cc->node_start->content);
	if ((check_for_builtin(lowletter_cmd, frame) != NONE) && (frame->single_com == ON))
	{
		prepare_builtin_alone(frame);
		execute_builtin(frame, lowletter_cmd);
		set_back_builtin_alone(frame);
	}
	else
	{
		pid = ft_fork();
		signal(SIGINT, child_killer);
		signal(SIGQUIT, child_killer);
		if (pid == 0)
			ft_childprocess(frame, exec);
		else if (frame->single_com == OFF)
			ft_parent(exec, frame->cc);
	}
	free(lowletter_cmd);
	return (0);
}
