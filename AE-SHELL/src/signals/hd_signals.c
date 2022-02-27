/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:29:31 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:47:31 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_flag_hd(int action)
{
	static int	i;

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
		write(1, "\n", 1);
		rl_on_new_line();
		sig_flag_hd(ON);
		close(STDIN_FILENO);
	}
}

char	*get_heredoc_prompt(void)
{
	struct termios	term;
	char			*str;

	signal(SIGINT, new_prompt2);
	if (sig_flag_hd(SHOW) == ON)
		return (NULL);
	signal(SIGQUIT, SIG_IGN);
	if (tcgetattr(1, &term) == ERROR)
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
