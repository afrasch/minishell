#include "../includes/minishell.h"

int	is_alnum_uscore(char c)
{
	if (ft_isalnum(str[*i + 1]) != NULL || str[*i +1] == '_')
		return (1);
	return(0);
}

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

}

void	expansion(char *str, int *i, t_frame *frame)
{
	t_var	*fake_list;
	char	*var_name;

	fake_list = init_fake_list();
	var_name = ft_calloc(1, sizeof(char))
	while (is_alnum_uscore(str[*i + 1]) == 1)
	{
		var_name = ft_add_chr_to_str(str, str[*i + 1]);
	}
	
}
