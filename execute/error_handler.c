/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 02:27:28 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/24 19:03:41 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_error(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("pipe error");
		exit(determine_exit_code(obj, Q_ERROR));
	}
}

int	fork_erro(t_obj *obj, int pid)
{
	if (pid == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("fork error");
		exit(determine_exit_code(obj, Q_ERROR));
	}
	return (pid);
}

void	dup2_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("dup2 error");
		exit(determine_exit_code(obj, Q_ERROR));
	}
}


int	dup_error(t_obj *obj, int dup)
{
	if (dup == -1)
	{
		ft_putstr_fd("minishell error: ", 2);
		perror("dup error");
		exit(determine_exit_code(obj, Q_ERROR));
	}
	return (dup);
}
