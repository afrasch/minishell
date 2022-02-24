#include "minishell.h"

void	child_killer(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", STDIN_FILENO);
		rl_replace_line("", 0);
	}
}

void	child_killer_one_cmd(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		rl_replace_line("", 0);
	}
}
