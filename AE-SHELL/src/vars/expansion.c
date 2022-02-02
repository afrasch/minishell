#include "../includes/minishell.h"

/* t_var	*init_fake_list(void)
{
	t_var	*fake_node;
	t_var	*fake_node2;

	fake_node = malloc(1*sizeof(t_var));
	fake_node->name = "a";
	fake_node->con = "\"echo $b\"";
	fake_node2 = malloc(1*sizeof(t_var));
	fake_node2->name = "b";
	fake_node2->con = "hallo ";
	fake_node->next = fake_node2;
	fake_node2->next = NULL;
	return (fake_node);
} */

int	expand_prequ(t_frame *frame, char cur_c, char next_c)
{
	if (cur_c == '$' && frame->cc->quote_st != SINGLE_Q
		&& next_c != ' ' && next_c != '\0'
		&& (is_alnum_uscore(next_c) == 1 || next_c == '\'' || next_c == '\"'))
		return (1);
	return (0);
}

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
			else if (frame->cc->cn->content != NULL && str[i -1] == ' ' && str[i] != '\0')
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
	else if (frame->cc->cn->content != NULL && str[i -1] == ' ' && str[i] != '\0')
		next_node(frame);
	frame->cc->cn->word = DOUBLE_Q;
	while (str[i] != '\0')
	{
		add_letter(str[i], frame);
		i++;
	}
}

void	add_exp_node(char c, t_frame *frame)
{
	init_node(frame);
	set_quote_state(c, frame);
}

void	check_exp_var(char *var_name, t_frame *frame)
{
	frame->shell_env = frame->shell_env_start;
	while (frame->shell_env != NULL)
	{
		if (ft_strcmp(var_name, frame->shell_env->name) == 0)
		{
			if (!frame->cc->cn)
				init_node(frame);
			if (frame->cc->cn->quote_st == DOUBLE_Q)
				q_var_expansion(frame->shell_env->con, frame);
			else if (frame->cc->cn->quote_st == NO_Q)
				uq_var_expansion(frame->shell_env->con, frame);
		}
		frame->shell_env = frame->shell_env->next;
	}
	free(var_name);
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
