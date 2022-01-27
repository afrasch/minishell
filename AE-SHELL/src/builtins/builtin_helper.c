#include "../includes/minishell.h"

void	prepare_builtin_alone(t_frame *frame)
{
	frame->saved_in_fd = dup(STDIN_FILENO);
	frame->saved_out_fd = dup(STDOUT_FILENO);
	check_for_redir(frame);
	dup2(frame->cc->in_fd, STDIN_FILENO);
	dup2(frame->cc->out_fd, STDOUT_FILENO);
}



void	set_back_builtin_alone(t_frame *frame)
{
	close (frame->cc->in_fd);
	close (frame->cc->out_fd);
	dup2(frame->saved_in_fd, STDIN_FILENO) ;
	dup2(frame->saved_out_fd, STDOUT_FILENO);
	close(frame->saved_in_fd);
	close(frame->saved_out_fd);
}


char	*ft_unquote(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = ft_calloc(ft_strlen(str) - 1, sizeof(char *));
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
	if (str != NULL)
		free(str);
	return (ret);
}

char	*get_env_var(t_frame *frame, char *name)
{
	t_var	*var;
	char	*content;

	var = frame->shell_env_start;//mit original_env
	while (var != NULL)
	{
		if (ft_strncmp(name, var->name, ft_strlen(name)) == 0)
		{
			content = ft_unquote(var->con);
			return (content);
			// return (var->con);
		}
		var = var->next;
	}
	return (NULL);
}

void	update_env(t_frame *frame, char *name, char *content)
{
	t_var	*var;

	var = frame->shell_env_start;
	while (var != NULL)
	{
		if (ft_strncmp(name, var->name, ft_strlen(name)) == 0)
		{
			if (var->con != NULL)
				free(var->con);
			var->con = ft_strdup(content);
		}
		var = var->next;
	}
}
