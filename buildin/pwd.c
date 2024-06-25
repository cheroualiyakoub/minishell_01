/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:35:16 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 12:53:21 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(char **argv, t_obj *obj)
{
	char	path[200];

	(void)obj;
	(void)argv;
	if (getcwd(path, 200))
	{
		printf("%s\n", path);
		return (SUCCESS);
	}
	return (FAILURE);
}
