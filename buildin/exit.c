/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:51:00 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/24 22:24:08 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	determine_exit_code(t_obj *obj, int exit_code)
{
	obj->exit_code = exit_code;
	return (exit_code);
}

void	free_tools(t_obj *obj)
{
	free(obj->str);
	free_env(&obj->env);
	free(obj->tool.oldpwd);
	free(obj->tool.pwd);
	free_cmd(&obj->cmd);
}

int	ft_exit(char **argv, t_obj *obj)
{
	(void)argv;

	if (argv[1] != NULL)
	{
		printf("exit: too many args.\n");
		obj->exit_code = EXIT_FAILURE;
		return (FAILURE);
	}
	free_tools(obj);
	exit(obj->exit_code);
}
