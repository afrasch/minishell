#include "minishell.h"

int	ft_childprocess(t_frame *frame, t_exec *exec)
{
	int		i;

	i = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_for_pipe(frame);
	get_path(frame);
	if (!frame->cc->node_start)
		error_exit(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	// if (i == ERROR)
	// {
	// 	printf("check %s\n", frame->cc->node_start->content);
	// 		print_error_exit(frame, frame->cc->node_start->content, NULL, "command not found");
	// }
	// else 
	if (frame->single_com == ON && i != ERROR)
		execute_one_cmd(frame, exec);
	if (frame->cc->in_fd == PIPEIN)
		dup2(exec->tmp_fd, STDIN_FILENO);
	else
		dup2(frame->cc->in_fd, STDIN_FILENO);
	if (frame->cc->out_fd == PIPEOUT)
		dup2(exec->fd[1], STDOUT_FILENO);
	else
		dup2(frame->cc->out_fd, STDOUT_FILENO);
	if (frame->cc->out_fd != STDOUT_FILENO
		&& frame->cc->out_fd < 0)
		close(frame->cc->out_fd);
	if (frame->cc->in_fd != STDIN_FILENO
		&& frame->cc->in_fd < 0)
		close(frame->cc->in_fd);
	close(exec->fd[0]);
	close(exec->fd[1]);
	close(exec->tmp_fd);
	execute_cmd(frame, i, change_caps(frame->cc->node_start->content));
	error_exit(frame);//TODO
	return (0);
}

void	wait_for_childs(t_frame *frame)
{
	int	status[2];
	int	sig;

	status[E_STATUS] = 0;
	while (status[E_STATUS] != ERROR)
	{
		status[E_STATUS] = waitpid(-1, &status[STAT_LOC], 0);
		if (frame->pid == status[E_STATUS])
		{
			if (WIFEXITED(status[STAT_LOC]))//child process ended normally
				frame->e_status = WEXITSTATUS(status[STAT_LOC]);
			if (WIFSIGNALED(status[STAT_LOC]))//child process ended abnormally
			{
				sig = WTERMSIG(status[STAT_LOC]);//which signal caused child process to exit?
				print_signal_error(sig);
				ft_putnbr_fd(sig, STDERR_FILENO);
				write(STDERR_FILENO, "\n", 1);
				frame->e_status = 128 + WTERMSIG(status[STAT_LOC]);
			}
		}
	}
}
