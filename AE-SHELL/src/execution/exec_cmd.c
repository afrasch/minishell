#include "minishell.h"


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

int	execute_cmd(t_frame *frame, int i, char* cmd)
{
	if (i == -2)
		execve(cmd, list_to_arr(frame->cc->node_start), env_list_to_arr(frame));
	else
		execve(ft_strjoin(frame->paths[i], cmd), list_to_arr(frame->cc->node_start), env_list_to_arr(frame));
	// TODO print_error(); + exit(126) usw;
	error_exit(frame);

	return (0);
}
