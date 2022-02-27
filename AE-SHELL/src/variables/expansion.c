/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:41:02 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 23:18:08 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	make_node(t_frame *frame, int i, char *str)
{
	if (frame->cc->cn == NULL && frame->cc->cn->content != NULL)
		init_node(frame);
	else if ((frame->cc->cn->content != NULL
			&& str[i - 1] == ' ' && str[i] != '\0')
		|| (frame->cc->cn->quote_st == NO_Q && str[i] == '\''))
		next_node(frame);
	frame->cc->cn->word = DOUBLE_Q;
}

void	uq_var_expansion(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		add_letter('\0', frame);
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == ' ')
			i++;
		if (i == 0 || str[i - 1] == ' ')
			make_node(frame, i, str);
		if (str[i] != ' ')
			add_letter(str[i], frame);
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	q_var_expansion(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (frame->cc->cn == NULL && frame->cc->cn->content != NULL)
		init_node(frame);
	else if (frame->cc->cn->content != NULL
		&& str[i] != '\0' && check_spaces(str[i - 1]) == 1)
		next_node(frame);
	frame->cc->cn->word = DOUBLE_Q;
	while (str[i] != '\0')
	{
		add_letter(str[i], frame);
		i++;
	}
}

void	expand(char *str, int *i, t_frame *frame)
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
	check_exp_var(var_name, frame);
}
