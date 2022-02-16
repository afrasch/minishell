#include "minishell.h"

static int	is_valid_varname(char *name)
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
		// return (print_error(SHELLNAME, "export", name, "not a valid identifier"));
		return (print_error("export", name, "not a valid identifier"));
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

static void	split_env(char *str, t_frame *frame)
{
	char	*name;
	char	*content;
	int		find_nbr;

	find_nbr = ft_int_strchr(str, '=');
	name = ft_substr(str, 0, find_nbr);
	content = ft_substr(str, find_nbr + 1, ft_strlen(str) - find_nbr);
	content = ft_quote(content);
	free(str);
	add_var_node(frame, name, content, OFF);
}

void get_env(t_frame *frame)
{
	int	i;
	extern char** environ;

	i = 0;
	while (environ[i] != NULL)
	{
		split_env(ft_strdup(environ[i]), frame);
		i++;
	}
}
