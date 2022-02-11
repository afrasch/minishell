#include "minishell.h"

int	error_exit(t_frame *frame)
{
	char	*msg;

	msg = strerror(errno);//TODO
	// perror("SHELL SHOCK");
	// frame->e_status = ; TODO setzen
	// write(STDERR_FILENO, msg, ft_strlen(msg));
	// write(STDERR_FILENO, "\n", 1);
	reset_frame(frame);
	exit(frame->e_status);//aus child !
}

int 	print_error(int err_no, char *cmd, char *arg, char *message)//TODO schönere struktur, keine wiederholungen// gegen NULL strings absichern
{
	char *msg;//TODO ganz ohne hardcode und strcmp?

	msg = strerror(err_no);
	if (message == NULL && cmd != NULL && msg && !arg)
		printf("%s: %s: %s\n", SHELLNAME, cmd, msg);
	if (message == NULL && cmd != NULL && msg && arg)
		printf("%s: %s: %s: %s\n", SHELLNAME, cmd, arg, msg);
	else if (message == NULL && cmd == NULL && msg)
		printf("%s: %s\n", SHELLNAME, msg);
	else if (message && cmd && !arg)
	{
		if (msg && ft_strcmp(msg, message) == 0)
			printf("%s: %s: %s\n", SHELLNAME, cmd, msg);
		else if (ft_strcmp(message, "syntax error near unexpected token") == 0)
			printf("%s: %s `%s'\n", SHELLNAME, message, cmd);
		else if (ft_strcmp("syntax error near double quotes", message) == 0)
			printf("%s: %s: %s\n", SHELLNAME, message, cmd);
		else if (ft_strcmp("syntax error near single quotes", message) == 0)
			printf("%s: %s: %s\n", SHELLNAME, message, cmd);
		else if (ft_strcmp("is a directory", message) == 0)
			printf("%s: %s: %s\n", SHELLNAME, cmd, message);
		else if (ft_strcmp(message, "command not found") == 0)
		{
			printf("%s: %s: %s\n", SHELLNAME, cmd, message);
			exit (127);//TODO eigene error_print_exit() plus free
		}
	}
	else if (arg && ft_strcmp(message, "not a valid identifier") == 0)
		printf("%s: %s: `%s': %s\n", SHELLNAME, cmd, arg, message);
	return (ERROR);
}
