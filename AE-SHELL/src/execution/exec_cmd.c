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

int	execute_one_cmd(t_frame *frame, t_exec *exec)
{
	int	i;

	get_path(frame);
	i = get_access(frame, change_caps(frame->cc->node_start->content));
	if (i == ERROR)
		// return (print_error(SHELLNAME, frame->cc->node_start->content, NULL, "No such file or directory"));
		return (print_error(frame->cc->node_start->content, NULL, "No such file or directory"));
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
	// TODO

	if (errno == ENOENT)
		print_error_exit(frame, cmd, "No such file or directory");
	else if (errno == EACCES)
	{
		frame->e_status = 126;
		print_error_exit(frame, cmd, "Permission denied");
	}
	else
		// print_error_errno(SHELLNAME, cmd, NULL);
		print_error(cmd, NULL, NULL);

	return (ERROR);
}
