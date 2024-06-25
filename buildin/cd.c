/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:45:59 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/24 16:25:27 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(t_obj *obj)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_strdup("PWD=");
	oldpwd = ft_strdup("OLDPWD=");
	pwd = ft_strjoin2(pwd, obj->tool.pwd, 1);
	oldpwd = ft_strjoin2(oldpwd, obj->tool.oldpwd, 1);
	add_env(pwd, &obj->env);
	add_env(oldpwd, &obj->env);
	free(pwd);
	free(oldpwd);
}

int	ft_chdir(char *path)
{
	if (chdir(path) != 0)
	{
		printf("cd: no such file or directory: %s\n", path);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	swap_path(char **s1, char **s2)
{
	char	*tmp;

	tmp = ft_strdup(*s1);
	free(*s1);
	*s1 = ft_strdup(*s2);
	free(*s2);
	*s2 = ft_strdup(tmp);
}

int	ft_cd(char **argv, t_obj *obj)
{
	if (argv[1] == NULL)
		return (SUCCESS);
	else if (argv[2] != NULL)
	{
		printf("cd: no such file or directory: %s\n", argv[1]);
		return (FAILURE);
	}
	if (ft_strcmp(argv[1], "-") == 0)
	{
		if (ft_chdir(obj->tool.oldpwd) == FAILURE)
			return (FAILURE);
		swap_path(&obj->tool.oldpwd, &obj->tool.pwd);
	}
	else
	{
		if (ft_chdir(argv[1]) == FAILURE)
			return (FAILURE);
		free(obj->tool.oldpwd);
		obj->tool.oldpwd = ft_strdup(obj->tool.pwd);
		free(obj->tool.pwd);
		obj->tool.pwd = ft_strdup(argv[1]);
	}
	update_env(obj);
	return (SUCCESS);
}
