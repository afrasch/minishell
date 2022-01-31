#include "../includes/minishell.h"

void	ft_clear_nodes(t_node **current_node)
{
	t_node	*node;

	while ((*current_node) != NULL)
	{
		node = (*current_node)->prev;
		free((*current_node));
		(*current_node) = NULL;
		(*current_node) = node;
	}
}


void	delete_node(t_frame	*frame, t_node *node)
{
	if (node->prev == NULL)
	{
		if (node->next != NULL)
		{
			node->next->prev = NULL;
			frame->cc->node_start = node->next;
			frame->cc->cn = node->next;
		}
		else
			frame->cc->node_start = NULL;
	}
	else
	{
		if (node->next == NULL)
		{
			node->prev->next = NULL;
			frame->cc->cn = node->next;
		}
		else
		{
			node->prev->next = node->next;
			node->next->prev = node->prev;
			frame->cc->cn = node->next;
		}
	}
	free_node(node);
}

void	delete_var_node(t_frame	*frame, t_var *node)
{
	t_var *tmp;

	if (!node || !frame->shell_env_start)
		return ;
	tmp = frame->shell_env_start;
	if (tmp == node)
	{
		frame->shell_env_start = frame->shell_env_start->next;
		free(tmp->name);
		if (tmp->con)
			free(tmp->con);
		free(tmp);
		return ;
	}
	while (tmp->next && tmp->next != node)
		tmp = tmp->next;
	tmp->next = node->next;
	free(node->name);
	if (node->con)
		free(node->con);
	free(node);
}


int	var_lstsize(t_var *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	lstsize(t_node *lst)
{
	int	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**list_to_arr(t_node *node_start)
{
	t_node	*tmp;
	char	**arr;
	int		i;
	int		lst_size;

	i = 0;
	lst_size = lstsize(node_start);
	arr = calloc(lst_size + 1, sizeof(char *));
	tmp = node_start;
	while (tmp != NULL)
	{
		arr[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**env_list_to_arr(t_frame *frame)
{
	t_var	*var;
	char	**arr;
	char	*tmp_con;
	int		i;
	int		lst_size;

	i = 0;
	var = frame->shell_env_start;
	lst_size = var_lstsize(var);
	arr = calloc(lst_size + 1, sizeof(char *));
	while (var != NULL)
	{
		tmp_con = ft_unquote(var->con);
		arr[i] = ft_strdup(tmp_con);
		var = var->next;
		i++;
		if (!tmp_con)
			free(tmp_con);
	}
	arr[i] = NULL;
	return (arr);
}
