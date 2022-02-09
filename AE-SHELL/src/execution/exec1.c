#include "../includes/minishell.h"

int	execute_one_cmd(t_frame *frame, t_exec *exec)
{
	int	i;

	get_path(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	if (i == ERROR)
		return (print_error(errno, frame->cc->node_start->content, NULL, "No such file or directory"));
	dup2(frame->cc->in_fd, STDIN_FILENO);
	dup2(frame->cc->out_fd, STDOUT_FILENO);
	if (frame->cc->out_fd != STDOUT_FILENO)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO)
		close(frame->cc->in_fd);
	(void) exec;
	execute_cmd(frame, i, change_caps(frame->cc->node_start->content));
	return (0);
}


int	ft_childprocess(t_frame *frame, t_exec *exec)
{
	int		i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_for_pipe(frame);
	get_path(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	if (i == ERROR)
		print_error(errno, frame->cc->node_start->content, NULL, "command not found");
	else if (frame->single_com == ON)
		execute_one_cmd(frame, exec);
	if (frame->cc->in_fd == PIPEIN)
		dup2(exec->tmp_fd, STDIN_FILENO);
	else
		dup2(frame->cc->in_fd, STDIN_FILENO);
	if (frame->cc->out_fd == PIPEOUT)
		dup2(exec->fd[1], STDOUT_FILENO);
	else
		dup2(frame->cc->out_fd, STDOUT_FILENO);
	if (frame->cc->out_fd != STDOUT_FILENO)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO)
		close(frame->cc->in_fd);
	close(exec->fd[0]);
	close(exec->fd[1]);
	close(exec->tmp_fd);
	return (execute_cmd(frame, i, change_caps(frame->cc->node_start->content)));
}

void	ft_parent(t_frame *frame, t_exec *exec, t_chunk *cc)
{
	close(exec->fd[1]);
	close(exec->tmp_fd);
	exec->tmp_fd = dup(exec->fd[0]);
	close(exec->fd[0]);
	(void)cc;
	(void)frame;
}
// void	ft_parent(t_frame *frame, t_exec *exec, t_chunk *cc)//TODO wie protecten? segfault bei str = "<file1 | wc"
// {
// 	if (close(exec->fd[1]) == ERROR
// 		|| close(exec->tmp_fd) == ERROR)
// 		reset_frame(frame);
// 	exec->tmp_fd = dup(exec->fd[0]);
// 	if (close(exec->fd[0]) == ERROR)
// 		reset_frame(frame);
// 	(void)cc;
// }

void execute_function(t_frame *frame, t_exec *exec)
{
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
		frame->pid = ft_fork();
		signal(SIGINT, child_killer);
		signal(SIGQUIT, child_killer);
		if (frame->pid == 0)
			ft_childprocess(frame, exec);//TODO if == ERROR protec
		else if (frame->single_com == OFF)
			ft_parent(frame, exec, frame->cc);
	}
	free(lowletter_cmd);
}
