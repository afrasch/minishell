#include "../includes/minishell.h"

static void	echo_init(t_frame *frame)
{
	frame->cc->built_in = B_ECHO;
	frame->nl = OFF;
}

int	echo(t_frame *frame)//TODO exit status bei error
{
	t_node	*node;

	echo_init(frame);
	node = frame->cc->node_start;
	if (!node->next || !node->next->content)
	{
		write (1, "\n", 1);
		return (0);
	}
	while (ft_strcmp(node->next->content, "-n") == 0)
	{
		node = node->next;
		if (!node->next)
			return (0);
		frame->nl = ON;
	}
	while (node->next)
	{
		node = node->next;
		write (frame->cc->out_fd, node->content, ft_strlen(node->content));
		if (node->next)
			write (frame->cc->out_fd, " ", 1);
	}
	if (frame->nl == OFF)
		write (1, "\n", 1);
	return (0);
}

int	cd(t_frame *frame)
{
	t_node *node;
	char	*home_path;
	char	*oldpwd;
	oldpwd = getcwd(NULL, 0);
	node = frame->cc->node_start;
	home_path = get_env_var(frame, "HOME");
	if (node->next == NULL)
	{
		chdir(home_path);//if == ERROR)
			// print_error();
	}
	else
		chdir(node->next->content);// if == ERROR
		// print_error();
	update_env(frame, "PWD", node->content, oldpwd);
	return (0);
}

int	pwd(t_frame *frame)
{
	char	*current_path;

	current_path = NULL;
	current_path = ft_strdup(getcwd(NULL, 0));
	write(frame->cc->out_fd, current_path, ft_strlen(current_path));
	write (frame->cc->out_fd, "\n", 1);
	return (0);
}

static void	print_export(t_frame *frame)
{
	t_var *var;

	var = frame->shell_env_start;
	while (var)
	{
		if (var->just_export == OFF && var->con)
			printf("declare -x %s=%s\n", var->name, var->con);
		else
			printf("declare -x %s\n", var->name);
		var = var->next;
	}
}

int	export(t_frame *frame)
{
	t_node	*node;
	char	*name;
	char	*content;
	char	*tmp;
	int		find_nbr;

	node = frame->cc->node_start;
	if (!node->next)
	{
		print_export(frame);
		return (0);
	}
	node = node->next;
	while (node)
	{
		find_nbr = ft_int_strchr(node->content, '=');
		if (find_nbr < 0)
			add_var_node(frame, node->content, NULL, ON);// NULL als just_export verwenden?
		else
		{
			node->content[find_nbr] = '"';
			name = ft_substr(node->content, 0, find_nbr);
			content = ft_substr(node->content, find_nbr, ft_strlen(node->content) - find_nbr);
			tmp = ft_add_chr_to_str(content, '"');
			add_var_node(frame, name, tmp, OFF);
		}
		node = node->next;
	}
	return (0);
}

int	unset(t_frame *frame)
{
	t_var *var;
	t_node *node;

	node = frame->cc->node_start;
	while (node->next)
	{
		var = frame->shell_env_start;
		node = node->next;
		while (var)
		{
			if (ft_strcmp(node->content, var->name) == 0)
			{
				delete_var_node(frame, var);
				break ;
			}
			var = var->next;
		}
	}
	return (0);
}

int	env(t_frame *frame)
{
	t_var *var;
	char *tmp_con;

	var = frame->shell_env_start;
	while (var)
	{
		if (var->just_export == ON)
		{
			var = var->next;
			continue ;
		}
		if (var->con)
		{
			tmp_con = ft_unquote(var->con);
			printf("%s=%s\n", var->name, tmp_con);
			if (tmp_con)
				free(tmp_con);
		}
		else
			printf("%s=\n", var->name);
		var = var->next;
	}
	return (0);
}

void	exit_minishell(t_frame *frame)
{
	reset_frame(frame);
	// system("leaks minishell");
	free_env(frame);//TODO why more leaks ?
	// destroy_all(frame);//plus env
	//close all fds
	ft_putstr_fd("exit\n", 2);//if builtin
//print_error ruft exit_minishell auf
	exit(EXIT_SUCCESS);
}

void	execute_builtin(t_frame *frame, char *cmd)//TODO builtins protection?
{
	if (check_for_builtin(cmd, frame) == B_ECHO)
		frame->e_status = echo(frame);
	else if (check_for_builtin(cmd, frame) == CD)
		frame->e_status = cd(frame);
	else if (check_for_builtin(cmd, frame) == PWD)
		frame->e_status = pwd(frame);
	else if (check_for_builtin(cmd, frame) == EXPORT)
		frame->e_status = export(frame);
	else if (check_for_builtin(cmd, frame) == UNSET)
		frame->e_status = unset(frame);
	else if (check_for_builtin(cmd, frame) == ENV)
		frame->e_status = env(frame);
	else if (check_for_builtin(cmd, frame) == EXIT)
		exit_minishell(frame);
}
