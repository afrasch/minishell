#include "../includes/minishell.h"

int	is_alnum_uscore(char c)
{
	if (ft_isalnum(c) != NULL || c == '_')
		return (1);
	return(0);
}



// t_env	*init_fake_list(void)
// {
// 	t_env	*fake_node;
// 	t_env	*fake_node2;

// 	fake_node = malloc(1*sizeof(t_env));
// 	fake_node->name = "a";
// 	fake_node->con = "echo $b";
// 	fake_node2 = malloc(1*sizeof(t_env));
// 	fake_node2->name = "b";
// 	fake_node2->con = "hallo";
// 	fake_node->next = fake_node2;
// 	fake_node2->next = NULL;
// }

char	*var_ident(t_env *var, char *str)
{
	while (var != NULL)
	{
		if (ft_strncmp(var->name, str, ft_strlen(str)) == 0)
			return (var->con);//if con empty -> NULL ?
		var = var->next;
	}
	return (NULL);
}

void	expansion(char *str, int *i, t_frame *frame)
{
	// t_env	*fake_list;
	t_env	*env;
	char	*var_name;
	char	*var_content;

	// fake_list = init_fake_list();
	var_name = ft_calloc(1, sizeof(char));
	var_content = ft_calloc(1, sizeof(char));
	while (is_alnum_uscore(str[*i + 1]) == 1) // error handling: wenn invalid char später kommt ist var
	{
		var_name = ft_add_chr_to_str(str, str[*i + 1]);
		(*i)++;
	}
	var_content = var_ident(env, var_name);//loopt durch env-list und schaut ob name vorhanden und wenn ja, ob content hinterlegt ist
	if (frame->expan != 1)
		split_in_chunks(var_content, frame);

	free(var_name);
	free(var_content);

	// fake_list->name = ft_strdup(var_name);
	// if (str[*i + 1] == '=')//go to first char of variable content
	// 	*i += 2;
	// while (str[*i] != ' ')
	// {
	// 	var_content = ft_add_chr_to_str(str, str[*i]);
	// 	(*i)++;
	// }
	// fake_list->con = ft_strdup(var_content);
}
