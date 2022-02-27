/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:28:09 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:13:41 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_to_arr(t_node *node_start, t_frame *frame)
{
	t_node	*tmp;
	char	**arr;
	int		i;
	int		lst_size;

	i = 0;
	lst_size = lstsize(node_start);
	arr = ft_calloc_mini(lst_size + 1, sizeof(char *), frame);
	tmp = node_start;
	while (tmp != NULL)
	{
		arr[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static char	**env_join(char **arr, t_var *var)
{
	char	*tmp_join;
	char	*tmp_con;
	int		i;

	i = 0;
	while (var != NULL)
	{
		tmp_con = ft_unquote(var->con);
		tmp_join = ft_strjoin("=", tmp_con);
		arr[i] = ft_strjoin(var->name, tmp_join);
		var = var->next;
		i++;
		if (tmp_join)
			free(tmp_join);
		if (tmp_con)
			free(tmp_con);
	}
	return (arr);
}

char	**env_list_to_arr(t_frame *frame)
{
	t_var	*var;
	char	**arr;
	int		lst_size;

	var = frame->shell_env_start;
	lst_size = var_lstsize(var);
	arr = ft_calloc_mini(lst_size + 1, sizeof(char *), frame);
	arr = env_join(arr, var);
	return (arr);
}
