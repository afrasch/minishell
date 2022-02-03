/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_chr_to_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 20:24:04 by elenz             #+#    #+#             */
/*   Updated: 2022/02/03 18:49:26 by afrasch          ###   ########.fr       */
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
	if (!str)
		free(str);
	str = NULL;
	new_string[length] = c;
	return (new_string);
}
