#include "../includes/minishell.h"

void	add_var_node(t_frame *frame, char *name, char *content)
{
	t_var	*node;

	node = ft_calloc(1, sizeof(t_var));
	node->con = content;
	node->name = name;
	node->next = NULL;
	if (frame->shell_env != NULL)
		frame->shell_env->next = node;
	else
		frame->shell_env_start = node;
	frame->shell_env = node;
}

void	split_env(char *str, t_frame *frame)
{
	char	*name;
	char	*content;
	char	*tmp;
	int		find_nbr;

	find_nbr = ft_int_strchr(str, '=');
	str[find_nbr] = '"';
	name = ft_substr(str, 0, find_nbr);//??
	content = ft_substr(str, find_nbr, ft_strlen(str) - find_nbr);
	tmp = ft_add_chr_to_str(content, '"');
	add_var_node(frame, name, tmp);
}

void get_env(t_frame *frame)
{
	int	i;
	extern char** environ;

	i = 0;

	while (environ[i] != NULL)
	{
		split_env(environ[i], frame);
		i++;
	}
}


int	main(void)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	get_env(&frame);
	//save_builtins(&frame);
	while (1)
	{
		str = init_signals_and_prompt(&frame);
		//str = "cat << 'end'";
		if (str == NULL)
		{
			write(1,"\n",1);
			break ;
		}
		if (str[0] != '\0')
		{
			if (ft_lexer(str, &frame) < 0)
				printf("\n***ERROR: SHELL SCHOCK***\n");
			add_history(str);
			reset_frame(str, frame);
		}
	}
}
