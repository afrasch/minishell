/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:50:29 by elenz             #+#    #+#             */
/*   Updated: 2021/11/01 12:53:29 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_line(char	**rest)
{
	int		nplace;
	char	*line;
	char	*ptrtofree;

	if (ft_gstrchr(*rest, '\n') != -1)
	{
		nplace = ft_gstrchr(*rest, '\n') + 1;
		line = ft_gsubstr(*rest, 0, nplace);
		ptrtofree = *rest;
		*rest = ft_gsubstr(*rest, nplace, (ft_gstrlen(*rest) - nplace));
		free (ptrtofree);
	}
	else
	{
		line = *rest;
		*rest = NULL;
	}
	return (line);
}

char	*get_next_line(int fd, int buffersize)
{
	char		*c;
	static char	*rest = NULL;
	int			readret;
	char		*line;

	if (fd < 0 || buffersize < 0)
		return (NULL);
	c = malloc((buffersize + 1) * sizeof(char));
	if (c == NULL)
		return (NULL);
	readret = 1;
	while (ft_gstrchr(rest, '\n') == -1 && readret > 0)
	{
		readret = read(fd, c, buffersize);
		if (readret == -1)
			return (ft_gfree_function(c, &rest));
		c[readret] = '\0';
		rest = ft_gstrjoin(rest, c);
	}
	if (rest[0] == '\0' || rest == NULL)
		return (ft_gfree_function(c, &rest));
	line = ft_line(&rest);
	free(c);
	return (line);
}
