/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:58:23 by elenz             #+#    #+#             */
/*   Updated: 2021/07/16 11:32:03 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	int				j;
	unsigned char	*z;
	unsigned char	*z2;

	i = 0;
	j = n;
	z = (unsigned char *)s1;
	z2 = (unsigned char *)s2;
	while (i < j)
	{
		if (z[i] != z2[i])
		{
			return (z[i] - z2[i]);
		}
		i++;
	}
	return (0);
}
