/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:12:15 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:22:23 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_frame *frame)
{
	free_env(frame);
	reset_frame(frame);
}

int	calc_ret(char *str)
{
	int	ret;

	ret = ft_atoi(str);
	if (ret < 0)
		return (256 + ret);
	if (ret > 255)
		return (256 % ret);
	return (ret);
}

int	check_input(t_frame *frame)
{
	t_node	*arg;
	char	*str;
	int		i;

	i = 0;
	arg = frame->cc->node_start->next;
	str = frame->cc->node_start->next->content;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			frame->e_status = 255;
			return (ERROR);
		}
		i++;
	}
	if (arg->next)
	{
		frame->e_status = 1;
		return (-2);
	}
	frame->e_status = calc_ret(str);
	return (0);
}

void	exit_minishell(t_frame *frame)
{
	t_node	*node;
	int		ret;

	ret = 0;
	node = NULL;
	if (frame->cc && frame->cc->node_start->next)
	{
		node = frame->cc->node_start;
		ret = check_input(frame);
	}
	if (ret == -1)
	{
		ft_putstr_fd("exit\n", 2);
		print_error("exit", node->next->content, "numeric argument requiered");
	}
	else if (ret == -2)
	{
		ft_putstr_fd("exit\n", 2);
		print_error("exit", NULL, "too many arguments");
		return ;
	}
	else if (frame->cc != NULL)
		ft_putstr_fd("exit\n", 2);
	free_all(frame);
	exit(frame->e_status);
}
// if (isatty(STDIN_FILENO)) TODO: MUSS DAS REIN?