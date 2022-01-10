/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 11:23:58 by elenz             #+#    #+#             */
/*   Updated: 2021/11/11 22:55:25 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	counter;
	size_t	i;
	char	*hay;
	char	*need;

	need = (char *)needle;
	hay = (char *)haystack;
	counter = 0;
	if (need[0] == '\0')
		return (hay);
	while (counter < len && hay[counter] != '\0')
	{	
		i = 0;
		while ((hay[counter + i] == need[i]) && ((counter + i) < len))
		{
			if (hay[counter + i] == need[i] && need[i + 1] == '\0')
				return (hay + counter);
			i++;
		}
		counter++;
	}
	return (0);
}
