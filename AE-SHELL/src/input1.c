#include "../includes/minishell.h"


/* void	part1(char *str)
{
	int	i;

	i = 0;
	while(str[i] != '\0')
	{
		if (ft_strrchr("<>| ", str[i]) != NULL)
		{
			i++;
			continue ;
		}
		printf("%c", str[i]);
		i++;
	}
} 
 */

void	handle_meta(char c, t_frame *frame)
{
	if (frame->current_node->content != NULL)
		next_node(frame);
	add_letter(c, frame);
}

void	set_quote_state(char c, t_frame *frame)
{
	if (c == '\"' && frame->current_node->quote_st == NO_Q)
	{
		frame->current_node->quote_st = DOUBLE_Q;
		return ;
	}
	if (c == '\''&& frame->current_node->quote_st == NO_Q)
	{
		frame->current_node->quote_st = SINGLE_Q;
		return ;
	}
	if (c == '\''&& frame->current_node->quote_st == SINGLE_Q)
	{
		frame->current_node->quote_st = NO_Q;
		return ;
	}
	if (c == '\"' && frame->current_node->quote_st == DOUBLE_Q)
	{
		frame->current_node->quote_st = NO_Q;
		return ;
	}
}

void	init_node(t_frame *frame)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->prev = NULL;
	node->next = NULL;
	frame->current_node = node;
	frame->current_node->quote_st = NO_Q;
	frame->node_start = frame->current_node;
}

void add_letter(char c, t_frame *frame)
{
	int		conlen;
	char	*new_string;

	conlen = ft_strlen(frame->current_node->content);
	new_string = ft_calloc(sizeof(char), (2 + conlen));
	if (frame->current_node->content != NULL)
	{
		ft_memcpy(new_string, frame->current_node->content, conlen);
		free(frame->current_node->content);
	}
	new_string[conlen] = c;
	frame->current_node->content = new_string;
}

void	split_in_nodes(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (frame->current_node == NULL)
		init_node(frame);
	while (str[i] != '\0')
	{
		if(frame->current_node->content != NULL)
			next_node(frame);
		while (str[i] == ' ' && frame->current_node->quote_st == NO_Q)
			i++;
		while ((ft_strrchr("<>| ", str[i]) == NULL && str[i] != '\0' && frame->current_node->quote_st == NO_Q)
		|| (frame->current_node->quote_st == DOUBLE_Q && str[i] != '\0') |
		(frame->current_node->quote_st == SINGLE_Q && str[i] != '\0'))
		{
			if (ft_strrchr("\"\'", str[i]) != NULL)
				set_quote_state(str[i], frame);
			add_letter(str[i], frame);
			i++;
		}
		while (ft_strchr("<>|", str[i]) != NULL && str[i] != '\0')
		{
			handle_meta(str[i], frame);
			i++;
		}
	}
	ft_print_stack(frame);
}

void	ft_lexer(char *str, t_frame *frame)
{
	split_in_nodes(str, frame);
	handle_quotes(frame);
}