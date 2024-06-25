/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utilis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:47:37 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/24 22:41:01 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pp_check_full_path(char *path_elemt, char *cmd)
{
	int		path_len;
	int		cmd_len;
	char	*full_path;

	if (path_elemt == NULL || cmd == NULL)
		return (NULL);
	path_len = ft_strlen(path_elemt);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(sizeof(char) * (path_len + cmd_len + 2));
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, path_elemt, path_len + 1);
	ft_strlcpy(full_path + path_len, "/", 2);
	ft_strlcpy(full_path + path_len + 1, cmd, cmd_len + 1);
	return (full_path);
}

char	*pp_get_path_env(t_obj *obj, char *cmd)
{
	t_env	*env_temp;
	char	**path_array;
	char	*cmd_path;
	int		i;

	env_temp = obj->env;
	path_array = NULL;
	while (env_temp && !path_array)
	{
		if (ft_strncmp(env_temp->value, "PATH=", 5) == 0)
			path_array = ft_split_simple(env_temp->value + 5, ':');
		env_temp = env_temp->next;
	}
	if (!path_array)
	{
		perror("couldns find path variables");
		exit (determine_exit_code(obj, Q_ERROR));
	}
	i = 0;
	while (path_array[i])
	{
		cmd_path = pp_check_full_path(path_array[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		i++;
		free (cmd_path);
	}
	return (NULL);
}

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
