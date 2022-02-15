/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 15:27:41 by elenz             #+#    #+#             */
/*   Updated: 2022/02/06 20:47:32 by afrasch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*string;
	size_t	i;
	size_t	a;

	if (s == NULL)
		return (0);
	i = 0;
	a = ft_strlen(&s[start]);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	if (a < len)
		len = a;
	string = (char *)ft_calloc(1, sizeof(char) * (len + 1));
	if (string == NULL)
		return (NULL);
	ft_strlcpy(string, &s[start], len + 1);
	return (string);
}
