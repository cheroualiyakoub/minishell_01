/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:53:24 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/25 09:56:28 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	front;
	size_t	end;
	size_t	len;
	char	*str;

	front = 0;
	end = ft_strlen((char *)s1);
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[front] && ft_strchr((char *)set, s1[front]))
		front++;
	while (end > front && s1[end - 1] && ft_strchr((char *)set, s1[end - 1]))
		end--;
	len = end - front;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (str)
	{
		ft_strlcpy(str, (char *)s1 + front, len + 1);
	}
	return (str);
}
