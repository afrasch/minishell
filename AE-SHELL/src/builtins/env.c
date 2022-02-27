/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 02:12:03 by elenz             #+#    #+#             */
/*   Updated: 2022/02/27 19:53:44 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_frame *frame)
{
	t_var	*var;
	char	*tmp_con;

	var = frame->shell_env_start;
	if (!var)
		return (1);
	while (var)
	{
		if (var->just_export == ON)
		{
			var = var->next;
			continue ;
		}
		if (var->con)
		{
			tmp_con = ft_unquote(var->con);
			printf("%s=%s\n", var->name, tmp_con);
			if (tmp_con)
				free(tmp_con);
		}
		else
			printf("%s=\n", var->name);
		var = var->next;
	}
	return (0);
}
