#include "minishell.h"

char	**add_slash(char **paths)
{
	int	i;

	i = 0;
	if (paths == NULL || *paths == NULL)
		return (NULL);
	while (paths[i])
	{
		paths[i] = ft_add_chr_to_str(paths[i], '/');
		i++;
	}
	return (paths);
}

void	get_path(t_frame *frame)
{
	t_var	*var;
	char	*tmp_path;

	var = frame->shell_env_start;
	if (!var)
		return ;
	while (var)
	{
		if ((look_for_var(frame, "PATH") == TRUE) && (ft_strcmp(var->name, "PATH") == 0))
		{
			tmp_path = ft_unquote(var->con);
			frame->paths = ft_split(tmp_path, ':');
			frame->paths = add_slash(frame->paths);
			free(tmp_path);
		}
		var = var->next;
	}
	if (!tmp_path)
		free(tmp_path);
}

int	get_access(t_frame *frame, char	*cmd)
{
	char	*tmp_argv;
	int		i;

	i = 0;
	if (access(cmd, F_OK) == 0)
		return (-2);//means: absolute path works-> no ERROR
	if (ft_strchr(cmd, '/') == 0 && frame->paths)
	{
		while (frame->paths[i])
		{
			tmp_argv = ft_strjoin(frame->paths[i], cmd);
			if (access(tmp_argv, F_OK) == 0)// || stat()
			{
				free(tmp_argv);
				tmp_argv = NULL;
				return (i);
			}
			if (tmp_argv != NULL)
				free(tmp_argv);
			tmp_argv = NULL;
			i++;
		}
	}
	else if (ft_strchr(cmd, '/') != 0 || !frame->paths)
	{
		frame->e_status = 127;
		print_error_exit(frame, cmd, "No such file or directory");
	}
	frame->e_status = 127;
	print_error_exit(frame, cmd, "command not found");
	return (ERROR);
}
