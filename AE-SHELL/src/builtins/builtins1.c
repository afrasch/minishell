#include "../includes/minishell.h"

void	echo(t_frame *frame)
{
	t_node	*node;

	node = frame->cc->node_start;
	if (node->next == NULL || node->next->content == NULL)//echo $a -> seg fault
		return ;
	node = node->next;
	frame->nl = OFF;
	while (ft_strcmp(node->content, "-n") == 0)
	{
		node = node->next;
		frame->nl = ON;
	}
	while (node->next != NULL)
	{
		write (frame->cc->out_fd, node->content, ft_strlen(node->content));
		write (frame->cc->out_fd, " ", 1);
		node = node->next;
	}
	write (1, node->content, ft_strlen(node->content));
	if (frame->nl != ON)
		write (1, "\n", 1);
	frame->cc->built_in = B_ECHO;
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

// void	split_env(char *str, t_frame *frame)
// {
// 	char	*name;
// 	char	*content;
// 	char	*tmp;
// 	int		find_nbr;

// 	find_nbr = ft_int_strchr(str, '=');
// 	str[find_nbr] = '"';
// 	name = ft_substr(str, 0, find_nbr);//??
// 	content = ft_substr(str, find_nbr, ft_strlen(str) - find_nbr);
// 	tmp = ft_add_chr_to_str(content, '"');
// 	add_var_node(frame, name, tmp);
// }

// void	export(t_frame *frame)
// {
// 	t_node *node;
// 	char *name;
// 	char *content;

// 	node = frame->cc->node_start;
// 	split_env(node->next->content, frame);
// }

void	env(t_frame *frame)
{
	t_var *var;
	char *tmp_con;

	var = frame->shell_env_start;
	while (var)
	{
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

void	execute_builtin(t_frame *frame, char *cmd)
{
	if (check_for_builtin(cmd, frame) == B_ECHO)
		echo(frame);
	else if (check_for_builtin(cmd, frame) == CD)
		cd(frame);
	else if (check_for_builtin(cmd, frame) == PWD)
		pwd(frame);
	// else if (check_for_builtin(cmd) == EXPORT)
	// 	export(frame);
	// else if (check_for_builtin(cmd) == UNSET)
	// 	unset(frame);
	// else if (check_for_builtin(cmd, frame) == ENV)
	// 	env(frame);
	// else if (check_for_builtin(cmd) == EXIT)
	// 	exit(frame);
}
