#include "minishell.h"

int	ft_fork()
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
		// exit(frame->e_status);

		//Error exit;
	}
	return (pid);
}

void	init_exec(t_exec *exec)
{
	exec->tmp_fd = dup(STDIN_FILENO);
	if (exec->tmp_fd < 0)
	{
		perror("");
		//TODO ERRORFUNCTION
	}
}

char	*change_caps(char *input_cmd)
{
	int	i;
	char	*lowletter_cmd;

	i = 0;
	lowletter_cmd = NULL;
	lowletter_cmd = calloc(ft_strlen(input_cmd) + 2, sizeof(char));
	while (input_cmd != NULL && input_cmd[i])
	{
		lowletter_cmd[i] = ft_tolower(input_cmd[i]);
		i++;
	}
	/* while (input_cmd != NULL && input_cmd[i])
	{
		lowletter_cmd = ft_add_chr_to_str(lowletter_cmd, ft_tolower(input_cmd[i]));
		i++;
	} */
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
