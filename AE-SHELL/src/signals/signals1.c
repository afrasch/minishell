#include "../includes/minishell.h"

/* void	switch_signal_print(int i, t_frame *frame)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		(void)frame;
		write(STDERR_FILENO, "Error while getting Attributes of Terminal\n", 43);
		exit(EXIT_FAILURE);
	}
	if (i == OFF)
		if ((term.c_lflag & (0x1 << 6)) == ECHOCTL)
	{
		term.c_lflag -= ECHOCTL;
		tcsetattr(1, TCSANOW, &term);
	}
	if (i == ON)
		if ((term.c_lflag & (0x1 << 6)) != ECHOCTL)
	{
		term.c_lflag += ECHOCTL;
		tcsetattr(1, TCSANOW, &term);
	}
	tcsetattr(0, 0, &term);
} */

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

int	sig_flag_hd(int action)
{
	static	int	i;

	if (action == ON)
		i = 1;
	else if (action == OFF)
		i = 0;
	return (i);
	
}
void	new_prompt2(int sig)
{
	if (sig == SIGINT)
	{
		write(1,"\n", 1);
		rl_on_new_line();
		sig_flag_hd(ON);
		close(STDIN_FILENO);
	}
}

void	clear_signals(void)
{
	struct termios	term;

	tcgetattr(1, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);
}

char *init_signals_and_prompt(t_frame *frame)
{
	struct termios	term;
	char			*str;

	sig_flag_hd(OFF);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (tcgetattr(1, &term) == -1)
	{
		write(STDERR_FILENO, "Error while getting Attributes of Terminal\n", 43);
		exit(EXIT_FAILURE);
	}
	if (term.c_lflag & ECHOCTL)
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, 0, &term);
	str = readline(PROMPT);
	clear_signals();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	(void)frame;
	return (str);
}

char	*get_heredoc_prompt()
{
	struct termios	term;
	char	*str;

	signal(SIGINT, new_prompt2);
	if (sig_flag_hd(SHOW) == ON)
		return (NULL);
	signal(SIGQUIT, SIG_IGN);
	if (tcgetattr(1, &term) == -1)
	{
		write(STDERR_FILENO, "Error while getting Attributes of Terminal\n", 43);
		exit(EXIT_FAILURE);
	}
	if (term.c_lflag & ECHOCTL)
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, 0, &term);
	str = readline("> ");
	signal(SIGINT, SIG_DFL);
	return (str);
}

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
