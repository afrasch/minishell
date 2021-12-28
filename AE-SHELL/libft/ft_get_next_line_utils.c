/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:54:18 by elenz             #+#    #+#             */
/*   Updated: 2021/11/01 12:54:31 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gstrlen(char	*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_gstrchr(char	*s, int c)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (-1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == '\0' && c == '\0')
		return (i);
	return (-1);
}

void	*ft_gfree_function(char *c, char **rest)
{
	free(c);
	free(*rest);
	*rest = NULL;
	return (NULL);
}

char	*ft_gsubstr(char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (ft_gstrlen(s) <= start)
		len = 0;
	substr = malloc((len + 1) * sizeof(char));
	while (i < len && s[start + i] != '\0')
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_gstrjoin(char *rest, char *c)
{
	int		full_len;
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (rest == NULL)
		rest = ft_gsubstr("", 0, 0);
	full_len = ft_gstrlen(rest) + ft_gstrlen(c);
	result = malloc((full_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (rest[++i] != '\0')
		result[i] = rest[i];
	while (c[j] != '\0')
	{
		result[i + j] = c[j];
		j++;
	}	
	result[i + j] = '\0';
	free(rest);
	return (result);
}
