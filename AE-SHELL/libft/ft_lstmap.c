/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:32:11 by elenz             #+#    #+#             */
/*   Updated: 2021/07/18 11:42:02 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*adresse;
	t_list	*newlist;
	t_list	*final;

	if (lst == NULL || f == NULL)
		return (NULL);
	final = ft_lstnew (f(lst->content));
	if (final == NULL)
		return (NULL);
	adresse = lst->next;
	while (adresse != 0)
	{
		newlist = ft_lstnew (f(adresse->content));
		if (newlist == NULL)
			ft_lstclear(&final, del);
		ft_lstadd_back(&final, newlist);
		lst = adresse;
		adresse = lst->next;
	}
	return (final);
}
