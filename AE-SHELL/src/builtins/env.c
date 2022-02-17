#include "minishell.h"

int	env(t_frame *frame)
{
	t_var	*var;
	char	*tmp_con;

	var = frame->shell_env_start;
	if (!var)
		return (2);
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
	return (0);
}
