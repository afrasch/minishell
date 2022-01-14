#include "../includes/minishell.h"

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

void	delete_next_node(t_node *node)
{
	t_node	*node_to_free;

	node_to_free = node->next;
	if (node->next->next != NULL)
	{
		node->next = node->next->next;
		node->next->prev = node;
	}
	else
		node->next = NULL;
	free_node (node_to_free);
}

void	fuse_arrows(t_frame *frame)
{
	while (frame->cc->cn != NULL)
	{
		if ((frame->cc->cn->content[0] == '>' && frame->cc->cn->word == NO_Q && frame->cc->cn->next != NULL) 
			&& (frame->cc->cn->next->content[0] == '>' && frame->cc->cn->next->word == NO_Q))
			{
				add_letter('>', frame);
				delete_next_node(frame->cc->cn);
			}
		if ((frame->cc->cn->content[0] == '<' && frame->cc->cn->quote_st == NO_Q && frame->cc->cn->next != NULL && frame->cc->cn->word != 2) 
			&& (frame->cc->cn->next->content[0] == '<' && frame->cc->cn->next->word == NO_Q))
			{
				add_letter('<', frame);
				delete_next_node(frame->cc->cn);
			}
		tag_node(frame->cc->cn);
		frame->cc->cn = frame->cc->cn->next;
	}
}

void	re_arrange_list(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		fuse_arrows(frame);
		frame->cc = frame->cc->next;
	}
}


