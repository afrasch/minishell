/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 19:08:42 by elenz             #+#    #+#             */
/*   Updated: 2022/02/15 22:29:29 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strinigfy(unsigned int n, int l, char *ptr)
{
	ptr[l] = '\0';
	l = l - 1;
	while (l > 0)
	{
		ptr[l] = (n % 10) + '0';
		n = n / 10;
		l--;
	}
	ptr[0] = (n % 10) + '0';
	return (ptr);
}

static int	lengthnbr(unsigned int n)
{
	int	counter;

	counter = 0;
	while (n > 0)
	{
		counter ++;
		n = n / 10;
	}
	return (counter);
}

char	*ft_utoa(unsigned int n)
{
	char			*number;
	int				len;

	if (n == 0)
		return (ft_strdup("0"));
	len = lengthnbr(n);
	number = (char *)malloc ((len + 1) * sizeof(char));
	if (number == NULL)
		return (NULL);
	number = strinigfy(n, len, number);
	return (number);
}
