#include "minishell.h"

char	*change_caps(char	*input_cmd)
{
	int	i;
	char	*lowletter_cmd;

	i = 0;
	lowletter_cmd = NULL;

	while (input_cmd[i])
	{
		lowletter_cmd = ft_add_chr_to_str(lowletter_cmd, ft_tolower(input_cmd[i]));
		i++;
	}
	return (lowletter_cmd);
}

t_builtin	check_for_builtin(char *input_cmd)
{
	t_builtin	builtin;

	if (ft_strcmp(input_cmd, "echo") == 0)
		builtin = ECHO;
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
	else
		builtin = NONE;
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
	int	i;

	i = 0;
	while (frame->original_env[i])
	{
		if (ft_strncmp(frame->original_env[i], "PATH=", 5) == 0)
		{
			frame->paths = ft_split(frame->original_env[i] + 5, ':');
			frame->paths = add_slash(frame->paths);
			//ft_free_2d((void***)frame->paths);
		}
		i++;
	}
}

int	get_access(t_frame *frame, char	*cmd)
{
	char	*tmp_argv;
	int		i;

	i = 0;
	while (frame->paths[i])
	{
		tmp_argv = ft_strjoin(frame->paths[i], cmd);
		if (access(tmp_argv, X_OK) == 0)
			return (i);
		if (tmp_argv != NULL)
			free(tmp_argv);
		tmp_argv = NULL;
		i++;
	}
	return (ERROR);
}

void	execute_cmd(t_frame *frame, int i, char* cmd)
{

	execve(ft_strjoin(frame->paths[i], cmd), list_to_arr(frame->cc->node_start), frame->original_env); 
	//ERROR, wenn hier hin kommt! 
}

void	executer(t_frame *frame, char *cmd)
{
	int		i;
	char	*lowletter_cmd;

	lowletter_cmd = change_caps(cmd);
	if (check_for_builtin(lowletter_cmd) == NONE)
	{
		get_path(frame);
		i = get_access(frame, lowletter_cmd);
		execute_cmd(frame, i, lowletter_cmd);
	}
	/* else
		execute_builtin(); */
}
