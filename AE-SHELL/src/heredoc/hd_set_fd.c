/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_set_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:17:09 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 14:26:27 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_hd_as_infd(t_frame *frame)
{
	t_node	*cn;

	cn = frame->cc->cn;
	if (frame->cc->in_fd >= 3)
		close(frame->cc->in_fd);
	frame->cc->in_fd = open(frame->cc->hd_path, O_RDONLY, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->e_status = 1;
		print_error(frame->cc->cn->next->content, NULL, NULL);
		return (ERROR);
	}
	delete_node(frame, frame->cc->cn);
	delete_node(frame, cn->next);
	return (0);
}

static int	creat_name(t_frame *frame)
{
	char	*name;
	char	*tmpdir;

	name = NULL;
	tmpdir = NULL;
	name = create_rand_name();
	if (look_for_var(frame, "TMPDIR") == TRUE)
		tmpdir = get_env_var(frame, "TMPDIR");
	else
	{
		ft_putendl_fd("SHELL SHOCK: heredoc: TMPDIR not set", STDERR_FILENO);
		free(name);
		frame->e_status = 1;
		return (ERROR);
	}
	frame->cc->hd_path = ft_strjoin(tmpdir, name);
	frame->cc->hd_bool = ON;
	add_hd_name_to_list(frame);
	free(name);
	free(tmpdir);
	name = NULL;
	return (0);
}

int	set_fd_here_doc(t_frame *frame)
{
	if (frame->cc->hd_bool == OFF)
	{
		if (creat_name(frame) == ERROR)
			return (ERROR);
	}
	else
		remove_hd(frame);
	frame->cc->in_fd = open(frame->cc->hd_path,
			O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (frame->cc->in_fd < 0)
	{
		frame->e_status = 1;
		print_error(frame->cc->cn->next->content, NULL, NULL);
		return (ERROR);
	}
	if (do_here_doc(frame) == ERROR)
		return (-1);
	close(frame->cc->in_fd);
	frame->cc->in_fd = STDIN_FILENO;
	return (0);
}

int	set_here_docs(t_frame *frame)
{
	if (frame->cc->in_fd > 3)
		close(frame->cc->in_fd);
	if (set_fd_here_doc(frame) == ERROR)
		return (ERROR);
	return (0);
}
