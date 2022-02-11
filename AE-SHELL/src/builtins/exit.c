#include "minishell.h"

void	exit_minishell(t_frame *frame)
{
	// system("leaks minishell");
	free_env(frame);//TODO why more leaks ? valgrind

	reset_frame(frame);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);//if builtin
//print_error ruft exit_minishell auf
	exit(EXIT_SUCCESS);
}
