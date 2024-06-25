/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:37:24 by ashirzad          #+#    #+#             */
/*   Updated: 2023/11/28 18:42:11 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memmove(void *dst, void *src, size_t len)
{
	char	*d_str;
	char	*s_str;
	size_t	count;

	count = len;
	s_str = src;
	d_str = dst;
	if (d_str > s_str)
	{
		while (count > 0)
		{
			d_str[count - 1] = s_str[count - 1];
			count--;
		}
	}
	else if (s_str > d_str)
	{
		ft_memcpy(d_str, s_str, len);
	}
	return (d_str);
}
