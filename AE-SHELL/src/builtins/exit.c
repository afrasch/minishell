#include "minishell.h"

void	free_all(t_frame *frame)
{
	free_env(frame);
	reset_frame(frame);
}

void	exit_minishell(t_frame *frame)
{
	free_all(frame);
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);//if builtin
	//system("leaks minishell");
	exit(frame->e_status);
}
