#include "../includes/minishell.h"

void	set_list_2start(t_frame *frame)
{
	frame->cc = frame->chunk_start;
	/* while (frame->cn->prev != NULL)
		frame->cn = frame->cn->prev; */
}

int	is_alnum_uscore(char c)
{
	if (ft_isalnum(c) != 0 || c == '_')
		return (1);
	return(0);
}

void ft_print_stack(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		printf("\nNew Chunk\n\n");
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			printf("%s\n", frame->cc->cn->content);
			printf("******\nwordstate= %d\n", frame->cc->cn->word);
			printf("IN FD FOR CHUNK: %i\n", frame->cc->in_fd);
			printf("NODE TYPE: %s\n*****\n", frame->cc->cn->typ);

			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}

void ft_print_stack_plain(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		printf("\nNew Chunk\n");
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			printf("%s\n", frame->cc->cn->content);
			/* printf("******\nwordstate= %d\n", frame->cc->cn->word);
			printf("IN FD FOR CHUNK: %i\n", frame->cc->in_fd);
			printf("NODE TYPE: %s\n*****\n", frame->cc->cn->typ); */

			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}

void	print_var(t_frame *frame)
{
	frame->shell_env = frame->shell_env_start;
	while (frame->shell_env != NULL)
	{
		printf("name: %s, content: %s \n", frame->shell_env->name, frame->shell_env->con);
		frame->shell_env = frame->shell_env->next;
	}
}

// void	ft_skip_char(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str && str[i] != c)
// 	{
// 		write(1, str[i], 1);
// 		i++;
// 	}
// 	i++;
// 	while (str && str[i] != c)
// 	{
// 		write(1, str[i], 1);
// 		i++;
// 	}
// }

// "export" auch handeln? -> zählt zusätzlich zu env auch variables ohne '=' auf
void	print_env(t_var *var)// aufgerufen if (ft_strncmp(str, "var", 3) == 0)
{
	while (var != NULL && var->con != NULL)
	{
		if (var->con != NULL)
			printf("%s=%s\n", var->name, var->con);
		else
			printf("%s=\n", var->name);
		var = var->next;
	}
}


void	debug_print(t_frame *frame)
{
	printf("\n___________________\n\n");
	t_node *node;
	t_node *node_tmp;


	node_tmp = frame->cc->cn;
	if (errno != 0)
		printf("ERROR: %s\n", strerror(errno));
	if (frame->cc == NULL)
	{
		printf ("You can't use debug_print while cc is NULL\n");
		return ;
	}
	node = frame->cc->node_start;
	if (node != NULL)
		printf("Current command: %s\n", node->content);
	int i = 1;
	while (node != NULL)
	{
		if (node->type == WORD)
			printf("Node %d type is \"word\"\n", i);
		if (node->type == PIPE)
			printf("Node %d type is \"|\"\n", i);
		if (node->type == S_REDIR_L)
			printf("Node %d type is \"<\"\n", i);
		if (node->type == S_REDIR_R)
			printf("Node %d type is \">\"\n", i);
		if (node->type == D_REDIR_L)
			printf("Node %d type is \"<<\"\n", i);
		if (node->type == D_REDIR_R)
			printf("Node %d type is \">>\"\n", i);
		node = node->next;
		i++;
	}
	if (frame->cc->in_fd == STDIN_FILENO)
		printf("Current input fd: STDIN\n");
	else
		printf("Current input fd: %d\n", frame->cc->in_fd);
	if (frame->cc->out_fd == STDOUT_FILENO)
		printf("Current output fd: STDOUT\n");
	else
		printf("Current output fd: %d\n", frame->cc->out_fd);
	printf("___________________\n");
	frame->cc->cn = node_tmp;
}

void	debug_print_full(t_frame *frame)
{
	printf("\n___________________\n\n");
	t_node *node;

	frame->cc = frame->chunk_start;
	while(frame->cc)
	{
		node = frame->cc->node_start;
		if (node != NULL)
			printf("Current command: %s\n", node->content);
		int i = 1;
		while (node != NULL)
		{
			if (node->type == WORD)
				printf("Node %d type is \"word\"\n", i);
			if (node->type == PIPE)
				printf("Node %d type is \"|\"\n", i);
			if (node->type == S_REDIR_L)
				printf("Node %d type is \"<\"\n", i);
			if (node->type == S_REDIR_R)
				printf("Node %d type is \">\"\n", i);
			if (node->type == D_REDIR_L)
				printf("Node %d type is \"<<\"\n", i);
			if (node->type == D_REDIR_R)
				printf("Node %d type is \">>\"\n", i);
			node = node->next;
			i++;
		}
		if (frame->cc->in_fd == STDIN_FILENO)
			printf("Current input fd: STDIN\n");
		else
			printf("Current input fd: %d\n", frame->cc->in_fd);
		if (frame->cc->out_fd == STDOUT_FILENO)
			printf("Current output fd: STDOUT\n");
		else
			printf("Current output fd: %d\n", frame->cc->out_fd);
		printf("___________________\n");
	frame->cc = frame->cc->next;
	}
	frame->cc = frame->chunk_start;
}