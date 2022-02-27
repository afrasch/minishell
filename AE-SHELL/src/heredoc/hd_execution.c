/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:03:18 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 14:14:09 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_here_doc_expansion(t_frame *frame, char *str)
{
	if (frame->cc->cn->next->word == NO_Q)
		handle_hd_expansion(frame, str);
	else
		ft_putendl_fd(str, frame->cc->in_fd);
}

int	do_here_doc(t_frame *frame)
{
	char	*str;
	char	*del;

	del = frame->cc->cn->next->content;
	while (1)
	{
		str = get_heredoc_prompt();
		if (!str)
			break ;
		if (ft_strcmp(str, del) == 0)
		{
			free (str);
			break ;
		}
		do_here_doc_expansion(frame, str);
		free(str);
	}
	if (sig_flag_hd(SHOW) == ON)
	{
		close(frame->cc->in_fd);
		return (ERROR);
	}
	return (0);
}

static int	start_dup_hd(t_frame *frame)
{
	int	std_in;

	frame->cc = frame->chunk_start;
	std_in = dup(STDIN_FILENO);
	if (std_in == ERROR)
		print_error("heredoc", NULL, "Dup fail");
	return (std_in);
}

static void	end_hd_dup(t_frame *frame, int std_in)
{
	frame->cc = frame->chunk_start;
	dup2(std_in, STDIN_FILENO);
	if (std_in == ERROR)
		print_error("heredoc", NULL, "Dup fail");
	close(std_in);
}

int	solve_heredocs(t_frame *frame)
{
	int	std_in;

	std_in = start_dup_hd(frame);
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
					if (std_in == ERROR)
						print_error("heredoc", NULL, "Dup fail");
					close(std_in);
					return (ERROR);
				}
			}
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
	end_hd_dup(frame, std_in);
	return (0);
}
