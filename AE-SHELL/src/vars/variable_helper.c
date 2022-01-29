#include "minishell.h"

char	*ft_unquote(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(ft_strlen(str) - 1, sizeof(char *));//where free?
	if (ret == NULL)
		return (NULL);
	while (str[j])
	{
		if (str[j] != '\"')
		{
			ret[i] = str[j];
			i++;
		}
		j++;
	}
	return (ret);
}

char	*ft_quote(char *str)
{
	char	*ret;
	int		j;

	j = 0;
	ret = ft_calloc(ft_strlen(str) + 3, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	ret[0] = '"';
	while (str[j])
	{
		ret[j + 1] = str[j];
		j++;
	}
	ret[j + 1] = '"';
	return (ret);
}

char	*get_env_var(t_frame *frame, char *name)
{
	t_var	*var;
	char	*content;

	var = frame->shell_env_start;
	while (var != NULL)
	{
		if (ft_strcmp(name, var->name) == 0)
		{
			content = ft_unquote(var->con);
			return (content);
		}
		var = var->next;
	}
	return (NULL);
}

/* Checks if a variable already exists in env.
   Returns TRUE (1) if yes. */
int	look_for_var(t_frame *frame, char *name)
{
	t_var *var;

	var = frame->shell_env_start;
	while (var)
	{
		if (ft_strcmp(name, var->name) == 0)
			return (TRUE);
		var = var->next;
	}
	return (FALSE);
}