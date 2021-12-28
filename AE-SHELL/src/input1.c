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
	next_node(frame);
	frame->current_node->quote_st = NO_Q;
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
	frame->current_node = node;
	frame->current_node->quote_st = NO_Q;
}

void add_letter(char c, t_frame *frame)
{
	int		conlen;
	char	*new_string;

	conlen = ft_strlen(frame->current_node->content);
	new_string = ft_calloc(sizeof(char), (2 + conlen));
	ft_memcpy(new_string, frame->current_node->content, conlen);
	new_string[conlen] = c;
	free(frame->current_node->content);
	frame->current_node->content = new_string;
}

void	part1(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (frame->current_node == NULL)
			init_node(frame);
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
		if (ft_strchr("<>| ", str[i]) != NULL && str[i] != '\0')
		{
			handle_meta(str[i], frame);
			i++;
		}
		printf("%s\n", frame->current_node->content);
	}
}

void	ft_lexer(char *str, t_frame *frame)
{
	part1(str, frame);
}