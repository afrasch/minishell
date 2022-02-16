#include "minishell.h"

static char	*expand_hd(char *str, int *i)
{
	char	*var_name;

	var_name = ft_calloc(1, sizeof(char));
	while (str[*i + 1] && (is_alnum_uscore(str[*i + 1])) == 1)
	{
		var_name = ft_add_chr_to_str(var_name, str[*i + 1]);
		(*i)++;
	}
	return (var_name);
}

void	handle_hd_expansion(t_frame *frame, char *str)
{
	int i = 0;
	char	*var_name = NULL;

	while (str[i])
	{
		if (str[i] == '$')
		{
			var_name = expand_hd(str, &i);
			var_name = get_env_var(frame, var_name);
			ft_putstr_fd (var_name, frame->cc->in_fd);
			if (var_name)
				free(var_name);
			var_name = NULL;//TODO eigene funktion ft_free
		}
		else
			ft_putchar_fd(str[i], frame->cc->in_fd);
		i++;
	}
	ft_putchar_fd('\n', frame->cc->in_fd);
}
