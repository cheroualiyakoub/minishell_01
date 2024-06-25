/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:57:16 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/28 22:48:25 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	len_d;
	size_t	len_s;

	x = 0;
	i = ft_strlen((char const *)dest);
	len_d = ft_strlen((char const *)dest);
	len_s = ft_strlen(src);
	if (size < 1)
		return (len_s);
	while (src[x] && i < size - 1)
	{
		dest[i] = src[x];
		i++;
		x++;
	}
	dest[i] = '\0';
	if (size < len_d)
		return (len_s + size);
	else
		return (len_d + len_s);
}
