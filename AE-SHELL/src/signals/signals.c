#include "minishell.h"

void	new_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_replace_line("", 0);
	}
	rl_on_new_line();
	rl_redisplay();
}


void	clear_signals(void)
{
	struct termios	term;

	tcgetattr(1, &term);//TODO error, exit
	term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);//TODO error, exit
}

char *init_signals_and_prompt(t_frame *frame)
{
	char			*str;
	struct termios	term;

	sig_flag_hd(OFF);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(1, &term) == -1)//TODO error, exit
		{
			write(STDERR_FILENO, "Error while getting Attributes of Terminal\n", 43);
			exit(EXIT_FAILURE);
		}
		if (term.c_lflag & ECHOCTL)
			term.c_lflag &= ~ECHOCTL;
		tcsetattr(1, 0, &term);//TODO error, exit
			str = readline(PROMPT);
	}
	else
	{
		str = minishell_get_next_line(STDIN_FILENO);
		if (str)
			str[ft_strlen(str) - 1] = '\0';//weil newline und tabs nicht berücksichtigt werden
	}
	clear_signals();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	(void)frame;
	return (str);
}
