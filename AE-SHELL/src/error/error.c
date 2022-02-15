#include "minishell.h"

int	error_exit(t_frame *frame)
{
	char	*msg;

	msg = strerror(errno);//TODO
	// perror("SHELL SHOCK");
	// frame->e_status = 0; TODO zurucksetzen
	// write(STDERR_FILENO, msg, ft_strlen(msg));
	// write(STDERR_FILENO, "\n", 1);
	reset_frame(frame);
	exit(frame->e_status);//aus child !
}

int	print_error_exit(char *cmd, char *arg, char *message)
{
	// char *msg;
	(void)arg;
	// msg = strerror(errno);
	if (ft_strcmp(message, "command not found") == 0)
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

// int	print_error(int err_no, char *cmd, char *arg, char *message)//TODO gegen NULL strings absichern
// {
// 	char *msg;

// 	msg = strerror(err_no);
// 	if (message == NULL && cmd != NULL && msg && !arg)
// 		printf("%s: %s: %s\n", SHELLNAME, cmd, msg);
// 	if (message == NULL && cmd != NULL && msg && arg)
// 		printf("%s: %s: %s: %s\n", SHELLNAME, cmd, arg, msg);
// 	else if (message == NULL && cmd == NULL && msg)
// 		printf("%s: %s\n", SHELLNAME, msg);
// 	else if (message && cmd && !arg)
// 	{
// 		if (msg && ft_strcmp(msg, message) == 0)
// 			printf("%s: %s: %s\n", SHELLNAME, cmd, msg);
// 		else if (ft_strcmp(message, "syntax error near unexpected token") == 0)
// 			printf("%s: %s `%s'\n", SHELLNAME, message, cmd);
// 		else if (ft_strcmp("syntax error near double quotes", message) == 0)
// 			printf("%s: %s: %s\n", SHELLNAME, message, cmd);
// 		else if (ft_strcmp("syntax error near single quotes", message) == 0)
// 			printf("%s: %s: %s\n", SHELLNAME, message, cmd);
// 		else if (ft_strcmp("is a directory", message) == 0)
// 			printf("%s: %s: %s\n", SHELLNAME, cmd, message);
// 	}
// 	else if (arg && ft_strcmp(message, "not a valid identifier") == 0)
// 		printf("%s: %s: `%s': %s\n", SHELLNAME, cmd, arg, message);
// 	return (ERROR);
// }

//tjensen-hepple lösung
int	print_error(char *s1, char *s2, char *s3, char *message)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
	{
		if (s1)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s2, 2);
	}
	if (s3)
	{
		if (s1 || s2)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(s3, 2);
	}
	if (message)
	{
		if (s1 || s2 || s3)
			ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
	}
	ft_putchar_fd('\n', 2);
	return (ERROR);
}

int	print_error_errno(char *s1, char *s2, char *s3)
{
	print_error(s1, s2, s3, strerror(errno));
	errno = 0;
	return (ERROR);
}

// void	exec_scmd_free_exit(int status, char **argv, t_list *l_free)
// {
// 	// exec_free_all(argv, l_free);
// 	exit(status);
// }
//TODO
//ENOMEM EINVAL...
