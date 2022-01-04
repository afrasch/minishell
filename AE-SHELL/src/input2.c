#include "../includes/minishell.h"

void	del_letter(int i, t_frame *frame)
{
	ft_memmove(&(frame->current_node->content)[i], &(frame->current_node->content)[i + 1],
	ft_strlen(frame->current_node->content) - i);
}

void expand_var(int i, t_frame *frame)
{
	if ((frame->current_node->content)[i] == '$' && frame->current_node->quote_st != SINGLE_Q)
	{
		if
	}
}

void	solve_quotes(t_frame *frame)
{
	int	i;
	char *str;

	i = 0;
	str = frame->current_node->content;
	while (str[i] != '\0')
	{
		expand_var(i, frame);
		if ((str[i]=='\"' && frame->current_node->quote_st != SINGLE_Q) ||
			(str[i]=='\'' && frame->current_node->quote_st != DOUBLE_Q))
		{
			set_quote_state(str[i], frame);
			del_letter(i, frame);
		}
		else
			i++;
	}
}

void handle_quotes(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->current_node != NULL)
	{
		solve_quotes(frame);
		frame->current_node = frame->current_node->next;
	}
}