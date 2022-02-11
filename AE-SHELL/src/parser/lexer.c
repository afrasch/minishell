#include "minishell.h"

void add_letter(char c, t_frame *frame)
{
	int		con_len;
	char	*new_string;

	if (!frame->cc->cn)
		return ;
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

static void	add_node(char c, char c_plus, t_frame *frame)
{
	int	i;

	i = 0;
	if (!frame->cc->cn)
		init_node(frame);
	if (ft_strchr("<> ", c) != NULL && frame->cc->cn->quote_st == NO_Q)
	{
		if ((frame->cc->cn->content != NULL
			&& (c_plus != ' ' && c_plus != '|' && c_plus != '\0')) ||
			(frame->cc->cn->content != NULL && ft_strchr("<>", c) != NULL))
			next_node(frame);
		if (c != ' ')
			add_letter(c, frame);
		if ((ft_strchr("<>", c) != NULL && (c_plus != ' ' && c_plus != '|' && c_plus != '\0')))
			next_node(frame);
	}
	if((ft_strchr("<>| ", c) == NULL && frame->cc->cn->quote_st == NO_Q)
	|| (frame->cc->cn->quote_st == DOUBLE_Q)
	|| (frame->cc->cn->quote_st == SINGLE_Q))
	{
		if (ft_strrchr("\"\'", c) != NULL)
			set_quote_state(c, frame);

		add_letter(c, frame);
	}
}

static void	add_e_status_node(t_frame *frame)//TODO signal permission denied = 126, Nsfod = 127 ???
{
	char	*e_status;
	int		i;

	i = 0;
	e_status = ft_itoa(frame->e_status);
	while (e_status[i])
	{
		add_letter(e_status[i], frame);
		i++;
	}
	if (e_status)
		free(e_status);
	if (frame->cc->cn)
		frame->cc->cn->type = WORD;
}

static void	split_in_chunks(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (frame->cc == NULL)
		init_chunk(frame);
	while (str[i] != '\0')
	{
		while (str[i] == ' ' && frame->cc->quote_st == NO_Q)
			i++;
		while ((ft_strchr("|", str[i]) == NULL && str[i] != '\0')
		|| (frame->cc->quote_st == DOUBLE_Q && str[i] != '\0')
		|| (frame->cc->quote_st == SINGLE_Q && str[i] != '\0'))
		{
			if (expand_requisites(frame, str[i], str[i + 1]) == 1)
				expand(str, &i, frame);
			else if (expand_requisites(frame, str[i], str[i + 1]) == 2)
			{
				add_e_status_node(frame);
				return ;
			}
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

int	ft_lexer(char *str, t_frame *frame)
{
	split_in_chunks(str, frame);
	handle_quotes(frame);
	re_arrange_list(frame); //TODO rename
	if (input_check(frame) < 0)
		return (ERROR);
	if (execute_chunks(frame) < 0)
	{
		if (sig_flag_hd(SHOW) == ON)
			clear_signals();//???
		return (ERROR);
	}
	return (0);
}
