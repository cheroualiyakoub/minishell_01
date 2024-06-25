/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:58:35 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/28 23:23:25 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	j;

	j = 0;
	while (n > 0 && s1[j] && s2[j] && s1[j] == s2[j])
	{
		j++;
		n--;
	}
	if (n == 0 || (s1[j] == '\0' && s2[j] == '\0'))
	{
		return (0);
	}
	else
	{
		return ((unsigned char)s1[j] - (unsigned char)s2[j]);
	}
}
