/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:53:21 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/27 21:51:43 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void	*s1, const void		*s2, size_t n)
{
	unsigned char	*u_s1;
	unsigned char	*u_s2;
	size_t			j;

	j = 0;
	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	while (j < n)
	{
		if (u_s1[j] != u_s2[j])
			return (u_s1[j] - u_s2[j]);
		j++;
	}
	return (0);
}
