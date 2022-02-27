/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 01:56:04 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:53:06 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_errors1(t_node *node, char *home_path)
{
	if (node->next == NULL)
	{
		if (chdir(home_path) == ERROR)
		{
			print_error(node->content, NULL, "Home path not available");
			return (1);
		}
	}
	else
	{
		if (chdir(node->next->content) == ERROR)
		{
			print_error(node->content, node->next->content, NULL);
			return (1);
		}
	}
	return (0);
}

int	cd(t_frame *frame)
{
	t_node	*node;
	char	*home_path;
	char	*oldpwd;

	node = frame->cc->node_start;
	home_path = get_env_var(frame, "HOME");
	oldpwd = get_env_var(frame, "OLDPWD");
	if (!oldpwd || !node || !home_path)
	{
		if (!oldpwd)
			print_error("cd", NULL, "OLDPWD not set");
		if (!home_path)
			print_error("cd", NULL, "HOME not set");
		return (1);
	}
	if (cd_errors1(node, home_path) == 1)
		return (1);
	update_env(frame, "PWD", node->content, oldpwd);
	free(home_path);
	home_path = NULL;
	return (0);
}
