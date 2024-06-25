/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:28:12 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/27 22:11:54 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t		needle_len;
	size_t		haystack_len;
	size_t		i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	if (needle_len > haystack_len || n < needle_len)
		return (NULL);
	while (i <= haystack_len - needle_len && i + needle_len <= n)
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
