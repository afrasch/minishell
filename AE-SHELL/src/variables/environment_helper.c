/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:37:15 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 18:23:28 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_unquote(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(ft_strlen(str) - 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (str[j])
	{
		if (str[j] != '\"')
		{
			ret[i] = str[j];
			i++;
		}
		j++;
	}
	return (ret);
}

char	*ft_quote(char *str, t_frame *frame)
{
	char	*ret;
	int		j;

	j = 0;
	ret = ft_calloc_mini(ft_strlen(str) + 3, sizeof(char *), frame);
	if (ret == NULL)
		return (NULL);
	ret[0] = '"';
	while (str[j])
	{
		ret[j + 1] = str[j];
		j++;
	}
	if (str)
		free(str);
	ret[j + 1] = '"';
	return (ret);
}

char	*get_env_var(t_frame *frame, char *name)
{
	t_var	*var;
	char	*content;

	var = frame->shell_env_start;
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0)
		{
			content = ft_unquote(var->con);
			return (content);
		}
		var = var->next;
	}
	return (NULL);
}

void	replace_env_var(t_frame *frame, char *name, char *new_content)
{
	t_var	*var;

	var = frame->shell_env_start;
	while (var)
	{
		if (ft_strcmp(name, var->name) == 0)
		{
			if (var->con)
				free(var->con);
			var->con = ft_quote(new_content, frame);
			return ;
		}
		var = var->next;
	}
}

/* Checks if a variable already exists in env.
   Returns TRUE (1) if yes. */
int	look_for_var(t_frame *frame, char *name)
{
	t_var	*var;

	var = frame->shell_env_start;
	while (var)
	{
		if (ft_strcmp(name, var->name) == 0)
			return (TRUE);
		var = var->next;
	}
	return (FALSE);
}
