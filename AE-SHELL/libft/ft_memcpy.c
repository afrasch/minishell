/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 10:24:49 by elenz             #+#    #+#             */
/*   Updated: 2022/02/06 20:44:03 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int		i;
	int		j;
	char	*dest1;
	char	*src1;

	j = n;
	i = 0;
	dest1 = (char *)dest;
	src1 = (char *)src;
	if (dest1 == NULL && src1 == NULL)
		return (dest);
	while (i < j)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest1);
}
