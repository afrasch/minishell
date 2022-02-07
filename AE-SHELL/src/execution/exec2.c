#include "minishell.h"

char	*change_caps(char *input_cmd)
{
	int	i;
	char	*lowletter_cmd;

	i = 0;
	lowletter_cmd = NULL;

	while (input_cmd != NULL && input_cmd[i])
	{
		lowletter_cmd = ft_add_chr_to_str(lowletter_cmd, ft_tolower(input_cmd[i]));
		i++;
	}
	return (lowletter_cmd);
}

t_builtin	check_for_builtin(char *input_cmd, t_frame *frame)
{
	t_builtin	builtin;

	builtin = NONE;
	if (input_cmd != NULL)
	{
		if (ft_strcmp(input_cmd, "echo") == 0)
			builtin = B_ECHO;
		else if (ft_strcmp(input_cmd, "cd") == 0)
			builtin = CD;
		else if (ft_strcmp(input_cmd, "pwd") == 0)
			builtin = PWD;
		else if (ft_strcmp(input_cmd, "export") == 0)
			builtin = EXPORT;
		else if (ft_strcmp(input_cmd, "unset") == 0)
			builtin = UNSET;
		else if (ft_strcmp(input_cmd, "env") == 0)
			builtin = ENV;
		else if (ft_strcmp(input_cmd, "exit") == 0)
			builtin = EXIT;
	}
	frame->cc->built_in = builtin;
	return (builtin);
}

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
	t_var *var;
	char *tmp_path;

	var = frame->shell_env_start;
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
	if (access(cmd, X_OK) == 0)
		return (-2);//means: absolute path works-> no ERROR
	while (frame->paths[i])
	{
		tmp_argv = ft_strjoin(frame->paths[i], cmd);
		if (access(tmp_argv, X_OK) == 0)
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
	frame->e_status = 127;
	return (ERROR);
	//TODO Frage: klappt nach unset das absolute command? Was passiert, wenn arg nicht get_access
}

int	execute_cmd(t_frame *frame, int i, char* cmd)
{
	if (i == -2)
		return (execve(cmd, list_to_arr(frame->cc->node_start), env_list_to_arr(frame)));
	else
		return (execve(ft_strjoin(frame->paths[i], cmd), list_to_arr(frame->cc->node_start), env_list_to_arr(frame)));
	//TODO ERROR, wenn hier hin kommt!
	return (0);
}
