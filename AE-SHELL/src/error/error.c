#include "minishell.h"

int	error_exit(t_frame *frame)
{
	//char	*msg;

	//msg = strerror(errno);//TODO
	// perror("SHELL SHOCK");
	// frame->e_status = 0; TODO zurucksetzen
	// write(STDERR_FILENO, msg, ft_strlen(msg));
	// write(STDERR_FILENO, "\n", 1);
	reset_frame(frame);
	exit(frame->e_status);//aus child !
}

int	print_error_exit(t_frame *frame, char *cmd, char *message)
{
	free_all(frame);

	if (ft_strcmp(message, "command not found") == 0
		|| ft_strcmp(message, "No such file or directory") == 0)
	{
		printf("%s: %s: %s\n", SHELLNAME, cmd, message);
		exit (127);
	}
	else if (ft_strcmp(message, "Permission denied") == 0)
	{
		printf("%s: %s: %s\n", SHELLNAME, cmd, message);
		exit (126);
	}
	return (ERROR);
}

int	print_error(char *cmd, char *arg, char *message)
{
	char *msg;

	msg = strerror(errno);
	ft_putstr_fd(SHELLNAME, STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (arg)
	{
		if (cmd)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
	}
	if (message)
	{
		if (cmd || arg)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
	}
	else if (msg)
	{
		if (cmd || arg)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	return (ERROR);
}

