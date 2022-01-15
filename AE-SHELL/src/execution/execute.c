#include "minishell.h"

char	*change_caps(char	*input_cmd)
{
	int	i;
	char	*lowletter_cmd;

	i = 0;
	while (input_cmd)
	{
		lowletter_cmd[i] = ft_tolower(input_cmd[i]);
		i++;
	}
	return (lowletter_cmd);
}

t_builtin	check_for_builtin(t_frame *frame, char *input_cmd)
{
	t_builtin	builtin;
	char		lowletter_cmd;

	lowletter_cmd = change_caps(input_cmd);
	if (ft_strcmp(lowletter_cmd, "echo") == 0)
		builtin = ECHO;
	if (ft_strcmp(lowletter_cmd, "cd") == 0)
		builtin = CD;
	if (ft_strcmp(lowletter_cmd, "pwd") == 0)
		builtin = PWD;
	if (ft_strcmp(lowletter_cmd, "export") == 0)
		builtin = EXPORT;
	if (ft_strcmp(lowletter_cmd, "unset") == 0)
		builtin = UNSET;
	if (ft_strcmp(lowletter_cmd, "env") == 0)
		builtin = ENV;
	if (ft_strcmp(lowletter_cmd, "exit") == 0)
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
	while (paths)
	{
		ft_add_chr_to_str(paths[i], '/');
		// printf("%s\n", paths[i]);
		i++;
	}
	return (paths);
}

void	get_path(t_frame *frame)
{
	extern char	**environ;
	int	i;
	char	**paths;

	i = 0;
	while (environ)
	{
		if (ft_strncmp(environ[i], "PATH=", 5) == 0)
		{
			paths = ft_split(environ[i] + 5, ':');
			frame->paths = add_slash(paths);
			ft_free_2d((void***)paths);
		}
		i++;
	}
}

int	get_access(t_frame *frame, char	*cmd)
{
	char	*tmp_argv;
	int		i;

	i = 0;
	while (frame->paths)
	{
		tmp_argv = ft_strjoin(frame->paths[i], cmd);//low letter cmd
		if (access(tmp_argv, X_OK) == 0)
		{
			frame->cc->cn->content = NULL;
			frame->cc->cn->content = ft_strdup(tmp_argv);
			return (i);
		}
		if (tmp_argv != NULL)
			free(tmp_argv);
		tmp_argv = NULL;
		i++;
	}
	return (ERROR);
}

void	execute_cmd(t_frame *frame, int i)
{
	char	**argv;
	extern char	**environ;

	argv = list_to_arr(frame->cc->node_start);

	execve(frame->paths[i], argv, environ);

}

void	executer(t_frame *frame, char *cmd)
{
	int	i;

	if (check_for_builtins(frame, cmd) == NONE)
	{
		get_path(frame);
		i = get_access(frame, cmd);
		execute_cmd(frame, i);
	}
	else
		execute_builtin();
}
