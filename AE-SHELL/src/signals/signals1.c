#include "../includes/minishell.h"

void	switch_signal_print(int i, t_frame *frame)
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
}

void	new_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(t_frame *frame)
{
	switch_signal_print(OFF, frame);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

/* void	child_quit(int pid)
{

} */

void	child_killer(int signal)
{
	kill(0, signal);
}

void	signals_for_child(t_frame *frame, int pid)
{
	struct sigaction sa;

	pid = 0;
	switch_signal_print(ON, frame);
	sa.sa_handler = child_killer;
	sigaction(SIGINT, &sa, NULL);
}