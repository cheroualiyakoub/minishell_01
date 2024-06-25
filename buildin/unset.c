/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:28:43 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 12:53:33 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove(t_env **env)
{
	t_env	*env_t;

	if (*env == NULL)
		return ;
	env_t = *env;
	if ((*env)->prev == NULL)
	{
		*env = (*env)->next;
		(*env)->prev = NULL;
	}
	else if ((*env)->next == NULL)
		(*env)->prev->next = NULL;
	else if ((*env)->prev && (*env)->next)
		(*env)->prev->next = (*env)->next;
	free(env_t);
}

void	delete_env(char *str, t_env **env)
{
	int		equal;
	t_env	*env_t;

	env_t = *env;
	while (env_t)
	{
		equal = check_equal(env_t->value);
		if ((ft_strncmp(str, env_t->value, ft_strlen(str)) == 0 \
			&& ft_strncmp(env_t->value, str, equal) == 0))
		{
			ft_remove(&env_t);
			break ;
		}
		env_t = env_t->next;
	}
}

int	ft_unset(char **argv, t_obj *obj)
{
	int	i;
	int	equal;

	i = 1;
	equal = 0;
	while (argv[i])
	{
		equal = check_equal(argv[i]);
		if (equal > 0)
		{
			printf("unset: %s: invalid parameter name\n", argv[i]);
			return (FAILURE);
		}
		else if (equal == -1)
		{
			printf("unset: not valid in this context: %s\n", argv[i]);
			return (FAILURE);
		}
		delete_env(argv[i], &obj->env);
		i++;
	}
	return (SUCCESS);
}
