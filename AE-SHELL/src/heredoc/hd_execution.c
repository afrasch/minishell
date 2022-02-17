#include "minishell.h"

int	do_here_doc(t_frame *frame)
{
	char	*str;
	char	*del;

	del = frame->cc->cn->next->content;

	while (1)
	{
		str = get_heredoc_prompt();
		// str = "end";
		if (!str)
			break ;
		if (ft_strcmp(str, del) == 0)
		{
			free (str);
			break ;
		}
		if (frame->cc->cn->next->word == NO_Q)
			handle_hd_expansion(frame, str);
		else
			ft_putendl_fd(str, frame->cc->in_fd);
		free(str);
	}
	if (sig_flag_hd(SHOW) == ON)
	{
		close(frame->cc->in_fd);
		return (ERROR);
	}
	return (0);
}

int	solve_heredocs(t_frame *frame)
{
	int		std_in;

	frame->cc = frame->chunk_start;
	std_in = dup(STDIN_FILENO);
	if (std_in  == ERROR)
		print_error("heredoc", NULL, "Dup fail");
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (frame->cc->cn->type == D_REDIR_L)
			{
				if (set_here_docs(frame) == ERROR)
				{
					dup2(std_in, STDIN_FILENO);
					if (std_in  == ERROR)
						print_error("heredoc", NULL, "Dup fail");
					close(std_in);
					return (ERROR);
				}
			}
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	frame->cc = frame->chunk_start;
	dup2(std_in, STDIN_FILENO);
	if (std_in  == ERROR)
		print_error("heredoc", NULL, "Dup fail");
	close(std_in);
	return (0);
}
