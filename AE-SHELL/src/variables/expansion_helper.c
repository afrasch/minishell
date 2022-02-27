/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:40:09 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:40:53 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_alnum_uscore(char c)
{
	if (ft_isalnum(c) != 0 || c == '_')
		return (1);
	return (0);
}

int	expand_requisites(t_frame *frame, char cur_c, char next_c)
{
	if ((cur_c == '$' && next_c == ' ')
		|| (cur_c == '$' && next_c == '\"' && frame->cc->quote_st == DOUBLE_Q)
		|| (cur_c == '$' && next_c == '\'' && frame->cc->quote_st == SINGLE_Q))
		return (0);
	if (cur_c == '$' && next_c == '?' && frame->cc->quote_st != SINGLE_Q)
		return (2);
	if (cur_c == '$' && frame->cc->quote_st != SINGLE_Q
		&& next_c != ' ' && next_c != '\0' && next_c != '	'
		&& (is_alnum_uscore(next_c) == 1 || next_c == '\'' || next_c == '\"'))
		return (1);
	return (0);
}

void	add_exp_node(char c, t_frame *frame)
{
	init_node(frame);
	set_quote_state(c, frame);
}

void	check_exp_var(char *var_name, t_frame *frame)
{
	frame->shell_env = frame->shell_env_start;
	while (frame->shell_env != NULL)
	{
		if (ft_strcmp(var_name, frame->shell_env->name) == 0)
		{
			if (!frame->cc->cn)
				init_node(frame);
			if (frame->cc->cn->quote_st == DOUBLE_Q)
				q_var_expansion(frame->shell_env->con, frame);
			else if (frame->cc->cn->quote_st == NO_Q)
				uq_var_expansion(ft_unquote(frame->shell_env->con), frame);
		}
		frame->shell_env = frame->shell_env->next;
	}
	frame->cc->expanded = ON;
	free(var_name);
}
