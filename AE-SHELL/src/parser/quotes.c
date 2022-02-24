#include "minishell.h"

static void	del_letter(int i, t_frame *frame)
{
	ft_memmove(&(frame->cc->cn->content)[i], &(frame->cc->cn->content)[i + 1],
	ft_strlen(frame->cc->cn->content) - i);
}

static int	solve_quotes(t_frame *frame)
{
	int	i;
	char *str;

	i = 0;
	str = frame->cc->cn->content;
	while (str[i] != '\0')
	{
		if ((str[i]=='\"' && frame->cc->cn->handle_quote != SINGLE_Q) ||
			(str[i]=='\'' && frame->cc->cn->handle_quote != DOUBLE_Q))
		{
			set_quote_state_2(str[i], frame);
			del_letter(i, frame);
			/* if (frame->cc->cn->content[0] == '\0')
			{
				delete_node(frame, frame->cc->cn);
				return (1);
			} */
		}
		else
			i++;
	}
	return (0);
}

void handle_quotes(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	while (frame->cc != NULL)
	{
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL && frame->cc->cn->content)
		{
			if (solve_quotes(frame) == 0)
				if (frame->cc->cn)
					frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}
