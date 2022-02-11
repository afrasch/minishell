#include "minishell.h"

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
