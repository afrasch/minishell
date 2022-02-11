#include "minishell.h"

void	print_signal_error(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd("Interrupt with signal ", STDERR_FILENO);
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit with signal ", STDERR_FILENO);
	if (sig == SIGABRT)
		ft_putstr_fd("Abort with signal ", STDERR_FILENO);
	if (sig == SIGTERM)
		ft_putstr_fd("Terminated with signal ", STDERR_FILENO);
	if (sig == SIGSEGV)
		ft_putstr_fd("Segmentation fault with signal ", STDERR_FILENO);//TODO bei here_docs am Anfang der Zeile richtig?
}
