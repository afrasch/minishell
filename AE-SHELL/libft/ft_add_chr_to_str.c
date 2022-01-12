/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_chr_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elenz <elenz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:24:04 by elenz             #+#    #+#             */
/*   Updated: 2022/01/09 14:35:42 by elenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

char	*ft_add_chr_to_str(char *str, char c)
{
	int		length;
	char	*new_string;

	length = ft_strlen(str);
	new_string = ft_calloc((length + 2), sizeof(char));
	ft_memcpy(new_string, str, length);
	free(str);
	new_string[length] = c;
	return (new_string);
}
