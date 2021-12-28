/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 09:49:20 by elenz             #+#    #+#             */
/*   Updated: 2021/07/16 11:32:51 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	p = (char *)s;
	j = n;
	while (i < j)
	{
		p[i] = c;
		i++;
	}
	return (s);
}
