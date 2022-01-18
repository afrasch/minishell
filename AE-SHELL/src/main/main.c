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
	name = ft_substr(str, 0, find_nbr);
	content = ft_substr(str, find_nbr, ft_strlen(str) - find_nbr);
	tmp = ft_add_chr_to_str(content, '"');
	add_var_node(frame, name, tmp);
}

void	copy_env_original(char **str, t_frame *frame)
{
	int i;
	int	ar_len;

	i = 0;
	ar_len = 0;
	while (str[ar_len] != NULL)
		ar_len++;
	frame->original_env = calloc(ar_len, sizeof(char *));
	while (str[i] != NULL)
	{
		frame->original_env[i] = ft_strdup(str[i]);
		i++;
	}
}

void get_env(t_frame *frame)
{
	int	i;
	extern char** environ;

	i = 0;

	copy_env_original(environ, frame);
	while (environ[i] != NULL)
	{
		split_env(environ[i], frame);
		i++;
	}
	add_var_node(frame,"a", "\0");
}


int	main(void)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	get_env(&frame);
	// save_builtins(&frame);
	while (1)
	{
		str = readline(PROMPT);//ctrl+D -> EOF
		//str = "$OS_ACTIVITY_DT_MODE";
		//str = "echo hallo | << end >file1 cat  <file2";
		//str = "e $a";
		//str = "ls -l";
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			exit(EXIT_SUCCESS);
		}
		if (str[0] != '\0')
		{
			if (ft_strncmp(str, "env", 3) == 0)
				print_env(frame.shell_env_start);
			if (ft_lexer(str, &frame) < 0)
				printf("\n***ERROR: SHELL SCHOCK***\n");
			add_history(str);
			// ft_print_stack(&frame);
		}
		reset_fd(&frame);
		// ft_print_stack_plain(&frame);


		//ft_print_stack(&frame);//prints with quotes
		//reset_frame(&frame);
		/* if (str != NULL)
		{
			//free(str);
			//str = NULL;
		} */
		//break ;
		// print_env(frame.shell_env_start);
	}
}
