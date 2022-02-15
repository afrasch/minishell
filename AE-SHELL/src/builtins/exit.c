#include "minishell.h"

void	exit_minishell(t_frame *frame)//take exit status for exit()
{
	free_env(frame);//TODO why more leaks ? valgrind
	reset_frame(frame);//try doppelpointer
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);//if builtin
	system("leaks minishell");
	//print_error ruft exit_minishell auf
	exit(EXIT_SUCCESS);//TODO right exit status of last cmd execution
}

