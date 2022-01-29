#include "../includes/minishell.h"

void	do_here_doc(t_frame *frame)
{
	char	*str;
	char	*del;
	int		i;

	i = 0;
	del = frame->cc->cn->next->content;
	while (1)
	{
		str = get_heredoc_prompt();
		//str = "end";
		if (str == NULL)
			break ;
		if (ft_strncmp(str, del, ft_strlen(del)) == 0)
			break ;
		if (frame->cc->cn->next->word != SINGLE_Q)
		{
			while (str[i])
			{
				// TODO expand_Dollars, wenn nicht SINGLE QUOTED
				i++;
			}
		}
		else
		{
			ft_putstr_fd (str, frame->cc->in_fd);
			ft_putstr_fd("\n", frame->cc->in_fd);
		}
	}
}

int	set_fd_here_doc(t_frame *frame)
{
	char	*name;

	if (frame->cc->hd_bool == OFF)
	{
		name = create_rand_name();
		frame->cc->hd_path = ft_strjoin("tmp/",name);
		frame->cc->hd_bool = ON;
	}
	else
		remove_hd(frame);
	frame->cc->in_fd  = open(frame->cc->hd_path, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));
		return (ERROR);
	}
	do_here_doc(frame);
	close(frame->cc->in_fd);
	frame->cc->in_fd = open(frame->cc->hd_path, O_RDONLY, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->cc->cc_errno = errno;
		perror(strerror(frame->cc->cc_errno));
		return (ERROR);
	}
	return (0);
}

int	set_here_docs(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd > 3)
		close(frame->cc->in_fd);
	if (set_fd_here_doc(frame) < 0)
		return (ERROR);
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

int	solve_heredocs(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (frame->cc->cn->type == D_REDIR_L)
			{
				if (set_here_docs(frame) < 0)
					return (ERROR);
			}
			else
				frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	frame->cc = frame->chunk_start;
	return (0);
}