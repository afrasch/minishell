/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 11:15:32 by elenz             #+#    #+#             */
/*   Updated: 2021/07/16 12:13:22 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*result;
	char	*a;

	len = ft_strlen(s) + 1;
	a = (char *)malloc(sizeof(char) * len);
	if (a == 0)
		return (0);
	result = ft_memcpy(a, s, len);
	return (result);
}
