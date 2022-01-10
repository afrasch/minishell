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

/* void	handle_meta(char c, t_frame *frame)
{
	if (frame->cn->content != NULL)
		next_node(frame);
	add_letter(c, frame);
} */

// void	set_quote_state(char c, t_frame)
// {
// 	if (c == '\"' && *quote_st == NO_Q)
// 	{
// 		*quote_st = DOUBLE_Q;
// 		*general_st = DOUBLE_Q;
// 		*cc_quote_st = DOUBLE_Q;
// 		return ;
// 	}
// 	if (c == '\''&& *quote_st == NO_Q)
// 	{
// 		*quote_st = SINGLE_Q;
// 		*general_st = SINGLE_Q;
// 		*cc_quote_st = SINGLE_Q;
// 		return ;
// 	}
// 	if (c == '\''&& *quote_st == SINGLE_Q)
// 	{
// 		*quote_st = NO_Q;
// 		*cc_quote_st = NO_Q;
// 		return ;
// 	}
// 	if (c == '\"' && *quote_st == DOUBLE_Q)
// 	{
// 		*quote_st = NO_Q;
// 		*cc_quote_st = NO_Q;
// 		return ;
// 	}
// }

void	set_quote_state(char c, t_frame *frame)
{
	if (c == '\"' && frame->cc->cn->quote_st == NO_Q)
	{
		frame->cc->cn->quote_st = DOUBLE_Q;
		frame->cc->cn->word = DOUBLE_Q;
		frame->cc->quote_st = DOUBLE_Q;
		return ;
	}
	if (c == '\''&& frame->cc->cn->quote_st == NO_Q)
	{
		frame->cc->cn->quote_st = SINGLE_Q;
		frame->cc->cn->word = SINGLE_Q;
		frame->cc->quote_st = SINGLE_Q;
		return ;
	}
	if (c == '\''&& frame->cc->cn->quote_st == SINGLE_Q)
	{
		frame->cc->cn->quote_st = NO_Q;
		frame->cc->quote_st = NO_Q;
		return ;
	}
	if (c == '\"' && frame->cc->cn->quote_st == DOUBLE_Q)
	{
		frame->cc->cn->quote_st = NO_Q;
		frame->cc->quote_st = NO_Q;
		return ;
	}
}

void	init_node(t_frame *frame)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	node->prev = NULL;
	node->next = NULL;
	frame->cc->cn = node;
	frame->cc->cn->quote_st = NO_Q;
	frame->cc->cn->word = NO_Q;
	frame->cc->node_start = frame->cc->cn;
}

void	init_chunk(t_frame *frame)
{
	t_chunk	*chunk;

	chunk = ft_calloc(1, sizeof(t_chunk));
	chunk->prev = NULL;
	chunk->next = NULL;
	frame->cc = chunk;
	frame->chunk_start = frame->cc;
}

void add_letter(char c, t_frame *frame)
{
	int		con_len;
	char	*new_string;

	con_len = ft_strlen(frame->cc->cn->content);
	new_string = ft_calloc(sizeof(char), (2 + con_len));
	if (frame->cc->cn->content != NULL)
	{
		ft_memcpy(new_string, frame->cc->cn->content, con_len);
		free(frame->cc->cn->content);
	}
	new_string[con_len] = c;
	frame->cc->cn->content = new_string;
}

//if "<><<>>|" -> META && entsprechende enum
void	add_node(char c, char c_plus, t_frame *frame)
{
	int	i;

	i = 0;

	if (!frame->cc->cn)
		init_node(frame);
	if ((ft_strchr("<> ", c) != NULL && frame->cc->cn->quote_st == NO_Q))
	{
		if (frame->cc->cn->content != NULL
			&& (c_plus != ' ' && c_plus != '|' && c_plus != '\0'))
			next_node(frame);
		if (c != ' ')
			add_letter(c, frame);
		//frame->cc->cn = frame->cc->cn->next;
	}
	if((ft_strchr("<>| ", c) == NULL && frame->cc->cn->quote_st == NO_Q)
	|| (frame->cc->cn->quote_st == DOUBLE_Q)
	|| (frame->cc->cn->quote_st == SINGLE_Q))
	{
		if (ft_strrchr("\"\'", c) != NULL)
			set_quote_state(c, frame);
		add_letter(c, frame);
	}
	// c != ' ' &&
	/* while (str[i] == ' ' && frame->cn->quote_st == NO_Q)
		i++;
	while ((ft_strrchr("<>| ", str[i]) == NULL && str[i] != '\0' && frame->cn->quote_st == NO_Q)
	|| (frame->cn->quote_st == DOUBLE_Q && str[i] != '\0')
	|| (frame->cn->quote_st == SINGLE_Q && str[i] != '\0'))
	{
		i++;
	}
	while (ft_strchr("<>|", str[i]) != NULL && str[i] != '\0')
	{
		handle_meta(str[i], frame);
		i++;
	}
	ft_print_stack(frame);//prints with quotes */
}

void	split_in_chunks(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (frame->cc == NULL)
		init_chunk(frame);
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && frame->cc->quote_st == NO_Q)
			i++;
		while ((ft_strchr("|",str[i]) == NULL && str[i] != '\0')
		|| (frame->cc->quote_st == DOUBLE_Q && str[i] != '\0')
		|| (frame->cc->quote_st == SINGLE_Q && str[i] != '\0'))
		{
			if (expand_prequ(frame, str[i], str[i + 1]))
				expand(str, &i, frame);
			else
				add_node(str[i], str[i + 1], frame);
			i++;
		}
		if (str[i] == '|')
		{
			next_chunk(frame);
			i++;
		}
	}
}



void	ft_lexer(char *str, t_frame *frame)
{
	split_in_chunks(str, frame);
	handle_quotes(frame);
}