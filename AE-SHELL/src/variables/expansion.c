#include "minishell.h"

void	uq_var_expansion(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		add_letter('\0', frame);
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		while (str[i] == ' ') //&& str[i + 1] == ' ')
			i++;
		if (i == 0 || str[i - 1] == ' ')
		{
			if (frame->cc->cn == NULL && frame->cc->cn->content != NULL)
				init_node(frame);
			else if (frame->cc->cn->content != NULL && str[i - 1] == ' ' && str[i] != '\0')
				next_node(frame);
			frame->cc->cn->word = DOUBLE_Q;
		}
		if (str[i] != ' ')
			add_letter(str[i], frame);
		i++;
	}
}

void	q_var_expansion(char *str, t_frame *frame)
{
	int	i;

	i = 0;
	if (frame->cc->cn == NULL && frame->cc->cn->content != NULL)
		init_node(frame);
	else if (frame->cc->cn->content != NULL && str[i] != '\0' && check_spaces(str[i - 1]) == 1)
		next_node(frame);
	frame->cc->cn->word = DOUBLE_Q;
	while (str[i] != '\0')
	{
		add_letter(str[i], frame);
		i++;
	}
}

void	expand(char *str, int *i, t_frame *frame)
{
	char	*var_name;

	var_name = ft_calloc(1, sizeof(char));
	while (str[*i + 1] && (is_alnum_uscore(str[*i + 1])) == 1)
	{
		var_name = ft_add_chr_to_str(var_name, str[*i + 1]);
		(*i)++;
	}
	check_exp_var(var_name, frame);
}
