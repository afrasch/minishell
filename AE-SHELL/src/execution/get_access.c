/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_access.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:49:46 by elenz             #+#    #+#             */
/*   Updated: 2022/02/25 00:31:50 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_slash(char **paths)
{
	int	i;

	i = 0;
	if (paths == NULL || *paths == NULL)
		return (NULL);
	while (paths[i])
	{
		paths[i] = ft_add_chr_to_str(paths[i], '/');
		i++;
	}
	return (paths);
}

void	get_path(t_frame *frame)
{
	t_var	*var;
	char	*tmp_path;

	var = frame->shell_env_start;
	if (!var)
		return ;
	while (var)
	{
		if ((look_for_var(frame, "PATH") == TRUE)
			&& (ft_strcmp(var->name, "PATH") == 0))
		{
			tmp_path = ft_unquote(var->con);
			frame->paths = ft_split(tmp_path, ':');
			frame->paths = add_slash(frame->paths);
			free(tmp_path);
		}
		var = var->next;
	}
	if (!tmp_path)
		free(tmp_path);
}

static int	check_access(t_frame *frame, char *cmd)
{
	int		i;
	char	*tmp_argv;

	i = 0;
	while (frame->paths[i])
	{
		tmp_argv = ft_strjoin(frame->paths[i], cmd);
		if (access(tmp_argv, F_OK) == 0)
		{
			free(tmp_argv);
			tmp_argv = NULL;
			return (i);
		}
		if (tmp_argv != NULL)
			free(tmp_argv);
		tmp_argv = NULL;
		i++;
	}
	return (ERROR);
}

int	get_access(t_frame *frame, char	*cmd)
{
	int		ret;

	ret = 0;
	if (check_for_builtin(cmd, frame) != NONE)
		return (0);
	if (access(cmd, F_OK) == 0)
		return (-2);
	if (ft_strchr(cmd, '/') == 0 && frame->paths)
	{
		ret = check_access(frame, cmd);
		if (ret != ERROR)
			return (ret);
	}
	else if (ft_strchr(cmd, '/') != 0 || !frame->paths)
	{
		frame->e_status = 127;
		print_error_exit(frame, cmd, "No such file or directory");
	}
	frame->e_status = 127;
	print_error_exit(frame, cmd, "command not found");
	return (ERROR);
}
