/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:14:49 by elenz             #+#    #+#             */
/*   Updated: 2022/03/16 21:10:27 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_hd(char *str, int *i, t_frame *frame)
{
	int		len;
	int		j;
	char	*var_name;

	len = 0;
	j = 0;
	while (str[*i + 1 + len] && (is_alnum_uscore(str[*i + 1 + len])) == 1)
		len++;
	var_name = ft_calloc_mini(len + 1, sizeof(char), frame);
	while (str[*i + 1] && (is_alnum_uscore(str[*i + 1])) == 1)
	{
		var_name[j] = str[*i + 1];
		j++;
		(*i)++;
	}
	return (var_name);
}

void	handle_hd_expansion(t_frame *frame, char *str)
{
	int		i;
	char	*var_name;
	char	*var_name1;

	i = 0;
	var_name = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = expand_hd(str, &i, frame);
			var_name1 = get_env_var(frame, var_name);
			free(var_name);
			var_name = NULL;
			ft_putstr_fd (var_name1, frame->cc->in_fd);
			free(var_name1);
			var_name1 = NULL;
		}
		else
			ft_putchar_fd(str[i], frame->cc->in_fd);
		i++;
	}
	ft_putchar_fd('\n', frame->cc->in_fd);
}
