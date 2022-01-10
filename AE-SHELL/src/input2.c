#include "../includes/minishell.h"

void	del_letter(int i, t_frame *frame)
{
	ft_memmove(&(frame->cc->cn->content)[i], &(frame->cc->cn->content)[i + 1],
	ft_strlen(frame->cc->cn->content) - i);
}

void	solve_quotes(t_frame *frame)
{
	int	i;
	char *str;

	i = 0;
	str = frame->cc->cn->content;
	while (str[i] != '\0')
	{
		if ((str[i]=='\"' && frame->cc->cn->quote_st != SINGLE_Q) ||
			(str[i]=='\'' && frame->cc->cn->quote_st != DOUBLE_Q))
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
	frame->cc = frame->chunk_start;
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			if (frame->cc->cn->content != NULL)
			{
				solve_quotes(frame);
				frame->cc->cn = frame->cc->cn->next;
			}
		}
		frame->cc = frame->cc->next;
	}
}
