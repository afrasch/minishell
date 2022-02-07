#include "../includes/minishell.h"

int	set_in_fd(t_frame *frame)
{

	frame->cc->in_fd = open(frame->cc->cn->next->content, O_RDONLY, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));
		return (ERROR);
	}
	return(0);
}

int	set_out_fd(t_frame *frame, char mode)
{
	if (mode == 's')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (mode == 'd')
		frame->cc->out_fd = open(frame->cc->cn->next->content, O_WRONLY|  O_APPEND | O_CREAT, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));
		return (ERROR);//TODO call errno in child
	}
	return (0);
}

int	set_right_red(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->out_fd >= 3)
		close(frame->cc->out_fd);
	if (cn->type == S_REDIR_R)
	{
		if (set_out_fd(frame, 's') < 0)
			return (ERROR);
	}
	else if (cn->type == D_REDIR_R)
	{
		if (set_out_fd(frame, 'd') < 0)
			return (ERROR);
	}
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int set_left_red(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd >= 3)
		close(frame->cc->in_fd);
	set_in_fd(frame);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

void	check_for_pipe(t_frame *frame)
{
	if (frame->cc->prev != NULL && frame->cc->in_fd < 3)
		frame->cc->in_fd = PIPEIN;
	if (frame->cc->next != NULL && frame->cc->out_fd < 3)
		frame->cc->out_fd = PIPEOUT;
}

int	check_for_redir(t_frame *frame)
{
	t_node	*cn;

	while (frame->cc->cn != NULL)
	{
		cn = frame->cc->cn;
		if (cn->type == S_REDIR_R || cn->type == D_REDIR_R)
		{
			if (set_right_red(frame) < 0)
				return (ERROR);
		}
		else if (cn->type == S_REDIR_L)
		{
			if (set_left_red(frame) < 0)
				return (ERROR);
		}
		else if (cn->type == D_REDIR_L)
			set_hd_as_infd(frame);
		else
			frame->cc->cn = frame->cc->cn->next;
	}
	return (0);
}

int prepare_pipe(t_exec *exec)
{
	if (pipe(exec->fd) < 0)
		print_error(errno, NULL, NULL, NULL);
	return (0);
}

void	print_signal_error(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: ", STDERR_FILENO);
	if (sig == SIGABRT)
		ft_putstr_fd("Abort: ", STDERR_FILENO);
	if (sig == SIGTERM)
		ft_putstr_fd("Terminated: ", STDERR_FILENO);
	if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault: ", STDERR_FILENO);
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
		execute_function(frame, &exec);
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
