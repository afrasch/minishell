#include "../includes/minishell.h"

int	is_valid_varname(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) != 0)
		return (FALSE);
	while (name[i])
	{
		if (name[i] != '_' && ft_isalnum(name[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	add_var_node(t_frame *frame, char *name, char *content, int just_export)//TODO absichern mit return val
{
	t_var	*node;

	if (is_valid_varname(name) == FALSE)
		return (print_error(errno, "export", name, "not a valid identifier"));
	node = ft_calloc(1, sizeof(t_var));
	if (!node)
		return (ERROR);
	node->con = ft_strdup(content);
	node->name = ft_strdup(name);
	free(content);
	content = NULL;
	free(name);
	name = NULL;
	node->just_export = just_export;
	node->next = NULL;
	frame->shell_env = frame->shell_env_start;
	while (frame->shell_env && frame->shell_env->next)
		frame->shell_env = frame->shell_env->next;
	if (frame->shell_env != NULL)
		frame->shell_env->next = node;
	else
		frame->shell_env_start = node;
	frame->shell_env = node;
	return (0);
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
	add_var_node(frame, name, tmp, OFF);
}

void get_env(t_frame *frame)
{
	int	i;
	extern char** environ;//TODO duplicate environ so that the original isnt changed

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
		//str = "cat << end <file1";
		//str = "\" echo \"  \" cat";
		//str = "export a b c d";
		// str = "<file1 | wc";
		if (str == NULL)
		{
			exit_minishell(&frame);
			break ;
		}
		if (str[0] != '\0')
		{
			ft_lexer(str, &frame);
			add_history(str);
			free(str);//SIGABRT
			reset_frame(&frame);
		}
	}
}

//TODO <<file OR <file1 -> Segmentation fault with signal 11 -> echo $? 139

//TODO : SIGNALS!!! Problem mit Delete und Problem mit Terminal man, Syntax falsche zeichen

//TODO funktionen: malloc + protection, print_error, free_all, exit+status