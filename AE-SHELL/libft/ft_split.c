/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 15:30:35 by elenz             #+#    #+#             */
/*   Updated: 2021/09/05 12:07:12 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countletter(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static size_t	ft_countwords(const char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (s[0] && s[0] != c)
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	*ft_allocate(char const *s, char c)
{
	size_t	i;
	size_t	charcount;
	char	*result;

	i = 0;
	charcount = ft_countletter(s, c);
	result = (char *)malloc(sizeof(char) * (charcount + 1));
	if (result == NULL)
	{
		free(result);
		return (NULL);
	}
	while (i < charcount)
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t		wordcount;
	char		**array;
	size_t		i;
	size_t		p;

	if (s == NULL)
		return (NULL);
	wordcount = ft_countwords(s, c) + 1;
	array = (char **)malloc(sizeof(char *) * wordcount);
	if (array == NULL)
		return (NULL);
	p = 0;
	i = 0;
	while (i < (wordcount - 1))
	{
		while (s[p] && s[p] == c)
			p++;
		array[i++] = ft_allocate(s + p, c);
		if (array == NULL)
			return (NULL);
		while (s[p] && s[p] != c)
			p++;
	}
	array[i] = NULL;
	return (array);
}
