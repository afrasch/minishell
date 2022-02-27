/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:30:13 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:20:11 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	tcgetattr(1, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &term);
}

static char	*get_str_and_set_term(void)
{
	struct termios	term;
	char			*str;

	if (tcgetattr(1, &term) == ERROR)
	{
		write(STDERR_FILENO,
			"Error while getting Attributes of Terminal\n", 43);
		exit(EXIT_FAILURE);
	}
	if (term.c_lflag & ECHOCTL)
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(1, 0, &term);
	return (str = readline(PROMPT));
}

char	*init_signals_and_prompt(t_frame *frame)
{
	char			*str;

	sig_flag_hd(OFF);
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
	if (isatty(STDIN_FILENO))
		str = get_str_and_set_term();
	else
	{
		str = minishell_get_next_line(STDIN_FILENO);
		if (str)
			str[ft_strlen(str) - 1] = '\0';
	}
	clear_signals();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	(void)frame;
	return (str);
}
