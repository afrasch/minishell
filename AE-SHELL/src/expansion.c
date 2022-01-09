#include "../includes/minishell.h"

typedef struct s_var
{
	char			*name;
	char			*con;
	struct s_var	*next;
}	t_var;


t_var	*init_fake_list(void)
{
	t_var	*fake_node;
	t_var	*fake_node2;

	fake_node = malloc(1*sizeof(t_var));
	fake_node->name = "a";
	fake_node->con = "echo $b";
	fake_node2 = malloc(1*sizeof(t_var));
	fake_node2->name = "b";
	fake_node2->con = "hallo";
	fake_node->next = fake_node2;
	fake_node2->next = NULL;
	return (fake_node);
}

int	is_alnum_uscore(char c)
{
	if (ft_isalnum(c) != 0 || c == '_')
		return (1);
	return(0);
}

void	check_for_var(char *var_name, t_frame *frame, t_var *fake_list)
{
	int	var_len;

	var_len = ft_strlen(var_name);
	frame->in_fd = 1;
	while (fake_list != NULL)
	{
		if (ft_strncmp(var_name, fake_list->name, var_len) == 0)
			printf("%s\n", fake_list->con);
		fake_list = fake_list->next;
	}

}

void	expand(char *str, int *i, t_frame *frame)
{
	t_var	*fake_list;
	char	*var_name;


	fake_list = init_fake_list();
	var_name = ft_calloc(1, sizeof(char));
	while (str[*i + 1] && (is_alnum_uscore(str[*i + 1])) == 1)
	{
		var_name = ft_add_chr_to_str(var_name, str[*i + 1]);
		printf("%s\n", var_name);
		(*i)++;
	}
	check_for_var(var_name, frame, fake_list);
	ft_print_stack(frame);
}
