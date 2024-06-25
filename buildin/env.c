/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:18:45 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/18 17:12:15 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **argv, t_obj *obj)
{
	t_env	*env;

	(void)argv;
	env = obj->env;
	while (env)
	{
		printf("%s\n", env->value);
		env = env->next;
	}
	return (0);
}
