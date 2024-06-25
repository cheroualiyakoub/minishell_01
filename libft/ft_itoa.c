/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:07:14 by ashirzad          #+#    #+#             */
/*   Updated: 2023/10/27 23:02:13 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size = 1;
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_reverse(int n)
{
	char	*arr;
	int		count;
	long	reverse_n;

	reverse_n = n;
	arr = (char *)malloc((sizeof(char) * ft_size(n)) + 1);
	if (reverse_n < 0)
		reverse_n *= -1;
	if (arr == NULL)
		return (NULL);
	count = 0;
	while (reverse_n != 0)
	{
		arr[count] = (reverse_n % 10) + 48;
		reverse_n /= 10;
		count++;
	}
	if (n < 0)
	{
		arr[count] = '-';
		arr[count + 1] = '\0';
	}
	else
		arr[count] = '\0';
	return (arr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		start;
	int		end;
	char	c;

	ptr = ft_reverse(n);
	if (ptr == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(ptr) - 1;
	if (n == 0)
		ptr[0] = '0';
	while (end > start)
	{
		c = ptr[start];
		ptr[start] = ptr[end];
		ptr[end] = c;
		start++;
		end--;
	}
	ptr[ft_size(n)] = '\0';
	return (ptr);
}
