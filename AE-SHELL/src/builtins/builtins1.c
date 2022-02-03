#include "../includes/minishell.h"

static void	echo_init(t_frame *frame)
{
	frame->cc->built_in = B_ECHO;
	frame->nl = OFF;
}

void	echo(t_frame *frame)
{
	t_node	*node;

	echo_init(frame);
	node = frame->cc->node_start;
	if (!node->next || !node->next->content)
	{
		write (1, "\n", 1);
		return ;
	}
	while (ft_strcmp(node->next->content, "-n") == 0)
	{
		node = node->next;
		if (!node->next)
			return ;
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
}

void	cd(t_frame *frame)
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
}

void	pwd(t_frame *frame)
{
	char	*current_path;

	current_path = NULL;
	current_path = ft_strdup(getcwd(NULL, 0));
	write(frame->cc->out_fd, current_path, ft_strlen(current_path));
	write (frame->cc->out_fd, "\n", 1);
}

void	print_export(t_frame *frame)
{
	t_var *var;

	var = frame->shell_env_start;
	while (var)
	{
		if (var->just_export == OFF)
			printf("declare -x %s=%s\n", var->name, var->con);
		else
			printf("declare -x %s\n", var->name);
		var = var->next;
	}
}

void	export(t_frame *frame)//TODO export a
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
		return ;
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
}

void	unset(t_frame *frame)
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
}

void	env(t_frame *frame)
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
}

void	exit_minishell(t_frame *frame)
{
	//free lists
	//free everything else
	//close all fds
	close(frame->saved_in_fd);
	close(frame->saved_out_fd);
	ft_putstr_fd("exit\n", 2);
	//if ()
	//print_error;?
	//get exit_value
	//exit(exit_value);
	exit(EXIT_SUCCESS);
}

void	execute_builtin(t_frame *frame, char *cmd)//TODO builtins protection?// exit status vorhanden?
{
	if (check_for_builtin(cmd, frame) == B_ECHO)
		echo(frame);
	else if (check_for_builtin(cmd, frame) == CD)
		cd(frame);
	else if (check_for_builtin(cmd, frame) == PWD)
		pwd(frame);
	else if (check_for_builtin(cmd, frame) == EXPORT)
		export(frame);
	else if (check_for_builtin(cmd, frame) == UNSET)
		unset(frame);
	else if (check_for_builtin(cmd, frame) == ENV)
		env(frame);
	else if (check_for_builtin(cmd, frame) == EXIT)
		exit_minishell(frame);
}
