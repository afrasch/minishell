/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_name_generator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:15:37 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 23:24:52 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_rand_name(void)
{
	int		fd;
	char	buf[10];
	int		i;

	fd = open("/dev/random", O_RDONLY);
	while (1)
	{
		i = 0;
		read(fd, buf, 9);
		buf[9] = '\0';
		while (buf[i])
		{
			buf[i] = (buf[i] * buf[i]) % 25 + 'a';
			i++;
		}
		if (access(buf, F_OK) == ERROR)
			break ;
	}
	close(fd);
	return (ft_strdup(buf));
}

void	add_hd_name_to_list(t_frame *frame)
{
	t_hd_list	*new_node;
	t_hd_list	*tmp;

	tmp = frame->hd_list;
	new_node = ft_calloc_mini(1, sizeof(t_hd_list), frame);
	if (tmp == NULL)
	{
		frame->hd_list = new_node;
		frame->hd_list->name_of_hd = ft_strdup(frame->cc->hd_path);
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		new_node->next = NULL;
		tmp->next = new_node;
		tmp->next->name_of_hd = ft_strdup(frame->cc->hd_path);
	}
}
