#include "minishell.h"

int set_hd_as_infd(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd >= 3)
		close(frame->cc->in_fd);
	frame->cc->in_fd = open(frame->cc->hd_path, O_RDONLY, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));
		return (ERROR);
	}
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int	set_fd_here_doc(t_frame *frame)
{
	char	*name;
	char	*tmpdir;
	t_chunk	*cc;

	name = NULL;
	tmpdir = NULL;
	cc = frame->cc;
	if (frame->cc->hd_bool == OFF)
	{
		name = create_rand_name();
		if (look_for_var(frame, "TMPDIR") == TRUE)
			tmpdir = get_env_var(frame, "TMPDIR");
		else
			exit_minishell(frame); // TODO error
		frame->cc->hd_path = ft_strjoin(tmpdir, name);
		// frame->cc->hd_path = ft_strjoin("tmp/",name);
		frame->cc->hd_bool = ON;
		add_hd_name_to_list(frame);
		free(name);
		name = NULL;
	}
	else
		remove_hd(frame);
	frame->cc->in_fd  = open(frame->cc->hd_path, O_RDWR | O_CREAT | O_TRUNC, 0777);//TODO open_protected
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));//TODO error, exit
		return (ERROR);
	}
	if (do_here_doc(frame) < 0)
		return (-1);
	if (close(frame->cc->in_fd) < 0)
		printf("ERROR HEREDOC\n");//TODO protect every open() and close()
	frame->cc->in_fd = STDIN_FILENO;
	return (0);
}

int	set_here_docs(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd > 3)
		close(frame->cc->in_fd);
	if (set_fd_here_doc(frame)< 0)
		return (-1);
	return (0);
}
