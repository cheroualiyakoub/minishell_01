/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 14:15:58 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/24 12:57:42 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_env(char *str, t_env **env)
{
	t_env	*env_t;
	int		equal;

	env_t = *env;
	equal = 0;
	while (env_t)
	{
		equal = check_equal(env_t->value);
		if ((ft_strncmp(str, env_t->value, check_equal(str)) == 0 \
			&& ft_strncmp(env_t->value, str, equal) == 0))
		{
			free(env_t->value);
			env_t->value = NULL;
			env_t->value = ft_strdup(str);
			return ;
		}
		env_t = env_t->next;
	}
	append_env(env, str);
}

int	ft_export(char **argv, t_obj *obj)
{
	int	i;
	int	equal;

	i = 1;
	equal = 0;
	while (argv[i])
	{
		equal = check_equal(argv[i]);
		if (equal == -1)
		{
			printf("export: not valid in this context: %s\n", argv[i]);
			return (FAILURE);
		}
		else if (equal != 0)
			add_env(argv[i], &obj->env);
		i++;
	}
	return (SUCCESS);
}
