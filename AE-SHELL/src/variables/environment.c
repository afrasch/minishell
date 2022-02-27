/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:38:02 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:38:51 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_varname(char *name)
{
	int	i;

	i = 0;
	if (name == NULL)
		return (FALSE);
	if (ft_isdigit(name[0]) != 0)
		return (FALSE);
	while (name[i])
	{
		if (name[i] != '_' && ft_isalnum(name[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	set_node_to_env(t_frame *frame, t_var *node)
{
	frame->shell_env = frame->shell_env_start;
	while (frame->shell_env && frame->shell_env->next)
		frame->shell_env = frame->shell_env->next;
	if (frame->shell_env != NULL)
		frame->shell_env->next = node;
	else
		frame->shell_env_start = node;
	frame->shell_env = node;
}

int	add_var_node(t_frame *frame, char *name, char *content, int just_export)
{
	t_var	*node;

	if (is_valid_varname(name) == FALSE)
	{
		frame->e_status = 1;
		return (print_error("export", name, "not a valid identifier"));
	}
	node = ft_calloc_mini(1, sizeof(t_var), frame);
	if (!node)
		return (ERROR);
	node->con = ft_strdup(content);
	node->name = ft_strdup(name);
	if (content)
		free(content);
	content = NULL;
	if (name)
		free(name);
	name = NULL;
	node->just_export = just_export;
	node->next = NULL;
	set_node_to_env(frame, node);
	return (0);
}

static void	split_env(char *str, t_frame *frame)
{
	char	*name;
	char	*content;
	int		find_nbr;

	find_nbr = ft_int_strchr(str, '=');
	name = ft_substr(str, 0, find_nbr);
	content = ft_substr(str, find_nbr + 1, ft_strlen(str) - find_nbr);
	content = ft_quote(content, frame);
	free(str);
	add_var_node(frame, name, content, OFF);
}

void	get_env(t_frame *frame, char **env)
{
	int			i;

	i = 0;
	while (env[i] != NULL)
	{
		split_env(ft_strdup(env[i]), frame);
		i++;
	}
}
