/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:40 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/24 22:23:47 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void) sig;
	rl_on_new_line();
	rl_replace_line("\n", 0);
	rl_redisplay();
}

void	init_obj(t_obj *obj, char **env)
{
	char	pwd[200];

	getcwd(pwd, 200);
	obj->str = NULL;
	obj->tool.pwd = ft_strdup(pwd);
	obj->tool.oldpwd = ft_strdup(pwd);
	obj->exit_code = 0;
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
	while (*env)
	{
		append_env(&obj->env, *env);
		env++;
	}
}

int	main(int args, char **argv, char **env)
{
	t_obj	obj;

	if (args == 2 || argv[1] != NULL)
	{
		printf("error : minishell accepts no argumnets.\n");
		return (FAILURE);
	}
	init_obj(&obj, env);
	while (1)
	{
		signal(SIGINT, sigint_handler);
		obj.str = readline("minishell -> ");
		parsing(&obj);
		add_history(obj.str);
		executor(&obj, env);
		free(obj.str);
		free_cmd(&obj.cmd);
	}
	return (0);
}
