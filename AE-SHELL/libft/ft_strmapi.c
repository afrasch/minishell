/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 13:09:07 by elenz             #+#    #+#             */
/*   Updated: 2021/07/16 12:14:44 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*string;
	unsigned int	i;

	if (s == NULL || f == NULL)
	{
		return (NULL);
	}
	i = 0;
	string = ft_strdup(s);
	if (string == NULL)
	{
		return (NULL);
	}
	while (string[i] != '\0')
	{
		string[i] = (*f)(i, string[i]);
		i++;
	}
	return (string);
}
