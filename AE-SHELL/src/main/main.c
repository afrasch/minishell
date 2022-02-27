/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:31:28 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 21:12:57 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_minishell(char *str, t_frame *frame)
{
	split_in_chunks(str, frame);
	handle_quotes(frame);
	re_arrange_list(frame);
	if (input_check(frame) == ERROR)
		return (ERROR);
	if (execute_chunks(frame) == ERROR)
	{
		if (sig_flag_hd(SHOW) == ON)
			clear_signals();
		return (ERROR);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char		*str;
	t_frame		frame;

	init_frame(&frame);
	get_env(&frame, env);
	while (1)
	{
		str = init_signals_and_prompt(&frame);
		if (str == NULL)
		{
			exit_minishell(&frame);
			free_all(&frame);
			exit(frame.e_status);
		}
		if (str[0] != '\0')
		{
			ft_minishell(str, &frame);
			add_history(str);
			free(str);
			reset_frame(&frame);
		}
	}
	(void)argc;
	(void)argv;
}
