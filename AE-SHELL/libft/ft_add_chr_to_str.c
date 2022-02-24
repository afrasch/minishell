/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_chr_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:24:04 by elenz             #+#    #+#             */
/*   Updated: 2022/02/24 01:51:16 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_add_chr_to_str(char *str, char c)
{
	int		length;
	char	*new_string;

	length = ft_strlen(str);
	new_string = ft_calloc((length + 2), sizeof(char));
	ft_memcpy(new_string, str, length);
	new_string[length] = c;
	return (new_string);
}
