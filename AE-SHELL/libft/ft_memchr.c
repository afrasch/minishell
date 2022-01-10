/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 11:42:57 by elenz             #+#    #+#             */
/*   Updated: 2021/07/18 11:13:44 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*z;
	unsigned int	i;

	z = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (z[i] == (unsigned char)c)
			return (z + i);
		i++;
	}
	return (0);
}
