#include "minishell.h"

void	set_quote_state(char c, t_frame *frame)
{
	if (c == '\"' && frame->cc->cn->quote_st == NO_Q)
	{
		frame->cc->cn->quote_st = DOUBLE_Q;
		frame->cc->cn->word = DOUBLE_Q;
		frame->cc->quote_st = DOUBLE_Q;
		frame->cc->cn->handle_quote = DOUBLE_Q;
		return ;
	}
	if (c == '\''&& frame->cc->cn->quote_st == NO_Q)
	{
		frame->cc->cn->quote_st = SINGLE_Q;
		frame->cc->cn->word = SINGLE_Q;
		frame->cc->quote_st = SINGLE_Q;
		frame->cc->cn->handle_quote = SINGLE_Q;
		return ;
	}
	if (c == '\''&& frame->cc->cn->quote_st == SINGLE_Q)
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
	if (c == '\''&& frame->cc->cn->quote_st == NO_Q)
	{
		frame->cc->cn->handle_quote = SINGLE_Q;
		return ;
	}
	if (c == '\''&& frame->cc->cn->quote_st == SINGLE_Q)
	{
		frame->cc->cn->handle_quote = NO_Q;
		return ;
	}
	if (c == '\"' && frame->cc->cn->quote_st == DOUBLE_Q)
	{
		frame->cc->cn->handle_quote = NO_Q;
		return ;
	}
}

void	tag_node(t_node *node)
{
	if (ft_strncmp(node->content, "<<", 2) == 0 && node->word == NO_Q)
	{
		node->type = D_REDIR_L;
		ft_strlcpy(node->typ, "here_doc", ft_strlen("here_doc\0") + 1);
	}
	else if (ft_strncmp(node->content, ">>", 2) == 0 && node->word == NO_Q)
	{
		node->type = D_REDIR_R;
		ft_strlcpy(node->typ, "append", ft_strlen("append") + 1);
	}
	else if (ft_strncmp(node->content, ">", 1) == 0 && node->word == NO_Q)
	{
		node->type = S_REDIR_R;
		ft_strlcpy(node->typ, "out_red", ft_strlen("out_red") + 1);
	}
	else if (ft_strncmp(node->content, "<", 1) == 0 && node->word == NO_Q)
	{
		node->type = S_REDIR_L;
		ft_strlcpy(node->typ, "in_red", ft_strlen("in_red") + 1);
	}
	else
	{
		node->type = WORD;
		ft_strlcpy(node->typ, "wort", ft_strlen("wort") + 1);
	}
}
