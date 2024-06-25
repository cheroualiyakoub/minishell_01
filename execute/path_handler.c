/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:14:50 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/17 15:19:54 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_full_path(char *path_elemt, char *cmd)
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

char	*get_full_path(char **env_path, char *cmd)
{
	int		i;
	char	*full_path;

	if (!env_path || !cmd)
		return (NULL);
	i = 0;
	while (env_path[i])
	{
		full_path = check_full_path(env_path[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
		free (full_path);
	}
	return (NULL);
}