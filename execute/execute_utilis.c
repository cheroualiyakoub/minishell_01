/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:47:37 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/25 22:29:13 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Close fds
 */
void	close_fds(int fd1, int fd2)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}

int	count_cmds(t_obj *obj)
{
	t_cmd	*cmd_temp;
	int		count;

	count = 0;
	cmd_temp = obj->cmd;
	while (cmd_temp)
	{
		count++;
		cmd_temp = cmd_temp->next;
	}
	return (count);
}

void	ft_wait_all(t_obj *obj, int *status)
{
	int	i;
	int	cmd_count;

	i = -1;
	cmd_count = count_cmds(obj);
	while (++i < cmd_count)
	{
		waitpid(obj->pid[i], status, 0);
		determine_exit_code(obj, *status);
	}
	free(obj->pid);
}
