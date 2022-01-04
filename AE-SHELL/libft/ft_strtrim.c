/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 12:21:26 by elenz             #+#    #+#             */
/*   Updated: 2021/07/16 13:05:16 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*result;
	int		len;

	if (s1 == NULL || set == NULL)
	{
		return (NULL);
	}
	i = 0;
	len = ft_strlen(s1);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
	{
		i++;
	}
	while (len > 0 && ft_strchr(set, s1[len - 1]))
	{
		len --;
	}
	if (len < i)
	{
		return (ft_strdup("\0"));
	}
	result = ft_substr(s1, i, len - i);
	return (result);
}
