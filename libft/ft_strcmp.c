/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:16:53 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/11 15:11:20 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	if (ft_strncmp(s1, s2, ft_strlen(s1)) != 0)
		return (-1);
	if (ft_strncmp(s2, s1, ft_strlen(s2)) != 0)
		return (-1);
	return (0);
}
