/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:20:35 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:54:38 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_frame *frame)
{
	char	*current_path;

	current_path = getcwd(NULL, 0);
	if (current_path == NULL)
		return (1);
	write(frame->cc->out_fd, current_path, ft_strlen(current_path));
	write (frame->cc->out_fd, "\n", 1);
	free(current_path);
	current_path = NULL;
	return (0);
}
