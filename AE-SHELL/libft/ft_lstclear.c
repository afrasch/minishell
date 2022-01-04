/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 22:40:14 by elenz             #+#    #+#             */
/*   Updated: 2021/07/16 12:12:12 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*temp2;

	if (lst == NULL || *lst == NULL)
		return ;
	temp = *lst;
	temp2 = *lst;
	*lst = NULL;
	while (temp != NULL)
	{
		temp2 = temp->next;
		if (del != NULL)
			del(temp->content);
		free(temp);
		temp = temp2;
	}
}
