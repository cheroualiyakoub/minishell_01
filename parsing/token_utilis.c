/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utilis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 22:46:56 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/25 22:49:53 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	set_char(char **str, char c)
{
	if (*(*str) == c)
		return (0);
	else
		return (*(*str));
}
