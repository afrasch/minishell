#include "minishell.h"

void	free_all(t_frame *frame)
{
	free_env(frame);
	reset_frame(frame);
}

void	exit_minishell(t_frame *frame)//take exit status for exit()
{
	// system("leaks minishell");
	free_all(frame);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);//if builtin
//print_error ruft exit_minishell auf
	exit(frame->e_status);//TODO right exit status of last cmd execution
}
