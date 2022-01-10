/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:59:15 by elenz             #+#    #+#             */
/*   Updated: 2021/07/21 10:50:24 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

int	ft_atoi(const char *nptr)
{
	long	i;
	char	*s;
	long	result;
	int		vorz;

	vorz = 1;
	s = (char *)nptr;
	result = 0;
	i = 0;
	while (((s[i] >= 9) && (s[i] <= 13)) || (s[i] == 32))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			vorz = -1;
		i++;
	}
	while (s[i] != '\0')
	{
		if (s[i] < 48 || s[i] > 57)
			return (vorz * result);
		result = result * 10 + s[i] - 48;
		i++;
	}
	return (vorz * result);
}
