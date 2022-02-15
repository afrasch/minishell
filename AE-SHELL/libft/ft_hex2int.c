/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex2int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 13:11:44 by elenz             #+#    #+#             */
/*   Updated: 2022/02/15 22:40:08 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

u_int32_t	hex2int(char *hex)
{
	u_int32_t	val;
	u_int8_t	byte;

	val = 0;
	while (*hex)
	{
		byte = *hex++;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - ('a' + 10);
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		val = (val << 4) | (byte & 0xF);
	}
	return (val);
}
