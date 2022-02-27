/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:29:17 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:46:47 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_double(t_frame *frame)
{
	frame->cc->cn->quote_st = DOUBLE_Q;
	frame->cc->cn->word = DOUBLE_Q;
	frame->cc->quote_st = DOUBLE_Q;
	frame->cc->cn->handle_quote = DOUBLE_Q;
}

static void	set_single(t_frame *frame)
{
	frame->cc->cn->quote_st = SINGLE_Q;
	frame->cc->cn->word = SINGLE_Q;
	frame->cc->quote_st = SINGLE_Q;
	frame->cc->cn->handle_quote = SINGLE_Q;
}

void	set_quote_state(char c, t_frame *frame)
{
	if (c == '\"' && frame->cc->cn->quote_st == NO_Q)
	{
		set_double(frame);
		return ;
	}
	if (c == '\'' && frame->cc->cn->quote_st == NO_Q)
	{
		set_single(frame);
		return ;
	}
	if (c == '\'' && frame->cc->cn->quote_st == SINGLE_Q)
	{
		frame->cc->cn->quote_st = NO_Q;
		frame->cc->quote_st = NO_Q;
		frame->cc->cn->handle_quote = NO_Q;
		return ;
	}
	if (c == '\"' && frame->cc->cn->quote_st == DOUBLE_Q)
	{
		frame->cc->cn->quote_st = NO_Q;
		frame->cc->quote_st = NO_Q;
		frame->cc->cn->handle_quote = NO_Q;
		return ;
	}
}

void	set_quote_state_2(char c, t_frame *frame)
{
	if (c == '\"' && frame->cc->cn->handle_quote == NO_Q)
	{
		frame->cc->cn->handle_quote = DOUBLE_Q;
		return ;
	}
	if (c == '\'' && frame->cc->cn->handle_quote == NO_Q)
	{
		frame->cc->cn->handle_quote = SINGLE_Q;
		return ;
	}
	if (c == '\'' && frame->cc->cn->handle_quote == SINGLE_Q)
	{
		frame->cc->cn->handle_quote = NO_Q;
		return ;
	}
	if (c == '\"' && frame->cc->cn->handle_quote == DOUBLE_Q)
	{
		frame->cc->cn->handle_quote = NO_Q;
		return ;
	}
}

void	tag_node(t_node *node)
{
	if (ft_strncmp(node->content, "<<", 2) == 0 && node->word == NO_Q)
		node->type = D_REDIR_L;
	else if (ft_strncmp(node->content, ">>", 2) == 0 && node->word == NO_Q)
		node->type = D_REDIR_R;
	else if (ft_strncmp(node->content, ">", 1) == 0 && node->word == NO_Q)
		node->type = S_REDIR_R;
	else if (ft_strncmp(node->content, "<", 1) == 0 && node->word == NO_Q)
		node->type = S_REDIR_L;
	else
		node->type = WORD;
}
