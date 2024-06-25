/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:33:12 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/28 23:16:04 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*get;

	get = 0;
	while (*str)
	{
		if (*str == (char) c)
		{
			get = (char *)str;
		}
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (get);
}
