#include "../includes/minishell.h"

char	*ft_get_path(char *com, char **env)
{
	int		i;
	int		j;
	char	**possible_path;
	char	*path;
	char	*path_slash;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	possible_path = ft_split(env[i] + 5, ':');
	while (possible_path[j] != NULL)
	{
		path_slash = ft_strjoin(possible_path[j], "/");
		path = ft_strjoin(path_slash, com);
		free(path_slash);
		if (access(path, X_OK) == 0)
			return (path);
		j++;
	}
	return (NULL); 
}

void	add_var_node(t_frame *frame, char *name, char *content)
{
	t_var	*node;

	node = calloc(1, sizeof(t_var));
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

void get_env(char **env, t_frame *frame)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		split_env(env[i], frame);
		i++;
	}
}


int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	get_env(env, &frame);
	while (1)
	{
		//str = readline(PROMPT);//ctrl+D -> EOF
		//str = "$OS_ACTIVITY_DT_MODE";
		str = "hi | hi";
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			exit(EXIT_SUCCESS);
		}
		if (str[0] != '\0')
		{
			ft_lexer(str, &frame);
			add_history(str);
			//ft_print_stack(&frame);
		}
		ft_print_stack(&frame);//prints with quotes
		//reset_frame(&frame);
		/* if (str != NULL)
		{
			//free(str);
			//str = NULL;
		} */
		break ;
	}
	(void)argc;
	(void)argv;
}
