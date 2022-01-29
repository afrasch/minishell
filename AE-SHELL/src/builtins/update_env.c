#include "minishell.h"


static void	update_oldpwd(t_frame *frame, char *oldpwd)
{
	t_var *tmp;

	tmp = frame->shell_env_start;
	if (look_for_var(frame, "OLDPWD") == TRUE)
	{
		while (tmp)
		{
			if ((ft_strcmp(tmp->name, "OLDPWD") == 0))
			{
				if (tmp->con)
					free(tmp->con);
				tmp->con = ft_strdup(ft_quote(oldpwd));
			}
			tmp = tmp->next;
		}
	}
	else
		add_var_node(frame, "OLDPWD", ft_quote(oldpwd), OFF);
}

static void	update_pwd(t_frame *frame)
{
	t_var *var;

	var = frame->shell_env_start;
	if (look_for_var(frame, "PWD") == TRUE)
	{
		while (var)
		{
			if (ft_strcmp(var->name, "PWD") == 0)
			{
				free(var->con);
				var->con = ft_strdup(ft_quote(getcwd(NULL, 0)));
				break ;
			}
			var = var->next;
		}
	}
}

void	update_env(t_frame *frame, char *name, char *content, char *oldpwd)
{
	t_var	*var;
	var = frame->shell_env_start;
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0)
		{
			if (ft_strcmp(name, "PWD") == 0)
			{
				update_oldpwd(frame, oldpwd);
				update_pwd(frame);
			}
			else
			{
				if (var->con != NULL)
					free(var->con);
				var->con = ft_strdup(content);
			}
		}
		var = var->next;
	}
}
