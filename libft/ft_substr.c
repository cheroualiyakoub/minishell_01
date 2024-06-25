/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:01:35 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/27 22:17:54 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	count;
	char	*ptr;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	ptr = (char *)malloc(len + 1);
	if (ptr == NULL)
		return (NULL);
	count = 0;
	while (count < len)
	{
		ptr[count] = s[start + count];
		count++;
	}
	ptr[count] = '\0';
	return (ptr);
}
