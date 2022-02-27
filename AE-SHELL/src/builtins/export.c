/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:13:25 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 21:23:04 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_export(t_frame *frame)
{
	t_var	*var;

	var = frame->shell_env_start;
	if (!var)
		return (2);
	while (var)
	{
		if (var->just_export == OFF && var->con)
			printf("declare -x %s=%s\n", var->name, var->con);
		else
			printf("declare -x %s\n", var->name);
		var = var->next;
	}
	return (0);
}

static void	replace_var(t_frame *frame)
{
	t_node	*node;
	char	*name;
	char	*con;
	int		del;

	node = frame->cc->node_start;
	node = node->next;
	while (node)
	{
		del = ft_int_strchr(node->content, '=');
		name = ft_substr(node->content, 0, del);
		con = ft_substr(node->content, del + 1, ft_strlen(node->content) - del);
		replace_env_var(frame, name, con);
		free(name);
		node = node->next;
	}
}

static void	add_var(t_frame *frame)
{
	t_node	*node;
	char	*name;
	char	*con;
	int		del;

	node = frame->cc->node_start;
	node = node->next;
	while (node)
	{
		del = ft_int_strchr(node->content, '=');
		if (del == ERROR)
			add_var_node(frame, ft_strdup(node->content), NULL, ON);
		else
		{
			name = ft_substr(node->content, 0, del);
			del += 1;
			con = ft_substr(node->content, del, ft_strlen(node->content) - del);
			con = ft_quote(con, frame);
			add_var_node(frame, name, con, OFF);
		}
		node = node->next;
	}
}

static int	error_val_varname(char *name)
{
	print_error("export", name, "not a valid identifier");
	free(name);
	return (1);
}

int	export(t_frame *frame)
{
	t_node	*node;
	char	*name;
	int		del_i;

	node = frame->cc->node_start;
	if (!node)
		return (1);
	if (!node->next)
		return (print_export(frame));
	node = node->next;
	del_i = ft_int_strchr(node->content, '=');
	if (del_i == 0)
	{
		print_error("export", "=", "not a valid identifier");
		return (1);
	}
	name = ft_substr(node->content, 0, del_i);
	if (is_valid_varname(name) == FALSE)
		return (error_val_varname(name));
	if (look_for_var(frame, name) == TRUE)
		replace_var(frame);
	else
		add_var(frame);
	free(name);
	return (0);
}
