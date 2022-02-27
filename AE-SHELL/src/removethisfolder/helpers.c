/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:44:24 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:45:33 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_stack(t_frame *frame)
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
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}

void	ft_print_stack_plain(t_frame *frame)
{
	set_list_2start(frame);
	while (frame->cc != NULL)
	{
		printf("\nNew Chunk\n");
		frame->cc->cn = frame->cc->node_start;
		while (frame->cc->cn != NULL)
		{
			printf("%s\n", frame->cc->cn->content);
			frame->cc->cn = frame->cc->cn->next;
		}
		frame->cc = frame->cc->next;
	}
}

/* void	debug_print(t_frame *frame)
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
} */

void	print_hd_list(t_frame *frame)
{
	t_hd_list	**node;

	node = &frame->hd_list;
	while ((*node)->next != NULL)
	{
		printf("%s\n", (*node)->name_of_hd);
		(*node) = (*node)->next;
	}
}
