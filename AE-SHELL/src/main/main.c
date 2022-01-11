#include "minishell.h"

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
	int		find_nbr;

	find_nbr = ft_int_strchr(str, '=');
	name = ft_substr(str, 0, find_nbr);
	content = ft_substr(str, find_nbr + 1, ft_strlen(str) - find_nbr);
	add_var_node(frame, name, content);
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
	while (1)
	{
		str = readline(PROMPT);//ctrl+D -> EOF
		// str = "$OS_ACTIVITY_DT_MODE";
		// str = "'    echo    hallo   '";
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			exit(EXIT_SUCCESS);
		}
		if (str[0] != '\0')
		{
			if (ft_strncmp(str, "env", 3) == 0)
				print_env(frame.shell_env_start);
			ft_lexer(str, &frame);
			add_history(str);
			//ft_print_stack(&frame);
		}
		ft_print_stack(&frame);
		//reset_frame(&frame);
		// if (str != NULL)
		// {
			// free(str);
		// 	str = NULL;
		// }
		// break ;
	}
}
