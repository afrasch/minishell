#include "minishell.h"

int	error_exit(t_frame *frame)
{
	reset_frame(frame);
	exit(frame->e_status);//aus child ! kein env freen
}

void	print_error_exit(t_frame *frame, char *cmd, char *message)
{
	free_all(frame);
	ft_putstr_fd(SHELLNAME, STDERR_FILENO);
	if (cmd)
		ft_putstr_fd(cmd, STDERR_FILENO);
	if (message)
	{
		if (cmd)
			ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
	}
	ft_putchar_fd('\n', STDERR_FILENO);
	exit (frame->e_status);
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

