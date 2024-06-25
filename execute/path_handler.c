/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:14:50 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/25 22:26:46 by ycheroua         ###   ########.fr       */
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

char	*pp_path_cheker(char **path_array, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
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

char	*pp_get_path_env(t_obj *obj, char *cmd)
{
	t_env	*env_temp;
	char	**path_array;

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
	return (pp_path_cheker(path_array, cmd));
}
