#include "../includes/minishell.h"

void	del_letter(int i, t_frame *frame)
{
	ft_memmove(&(frame->cn->content)[i], &(frame->cn->content)[i + 1],
	ft_strlen(frame->cn->content) - i);
}

void expand_var(int i, t_frame *frame)
{
	if ((frame->cn->content)[i] == '$' && frame->cn->quote_st != SINGLE_Q)
	{
		// if
		printf("just so compiling works %s\n", __func__);
	}
}

void	solve_quotes(t_frame *frame)
{
	int	i;
	char *str;

	i = 0;
	str = frame->cn->content;
	while (str[i] != '\0')
	{
		expand_var(i, frame);
		if ((str[i]=='\"' && frame->cn->quote_st != SINGLE_Q) ||
			(str[i]=='\'' && frame->cn->quote_st != DOUBLE_Q))
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
	while (frame->cn != NULL)
	{
		solve_quotes(frame);
		frame->cn = frame->cn->next;
	}
}
