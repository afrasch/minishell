/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_kill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:30:07 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 15:30:08 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
