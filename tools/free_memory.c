/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:10:28 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 13:05:01 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*current;
	t_lexer	*next;

	current = *lexer;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*lexer = NULL;
}

void	free_token(t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *cmd;
	while (current != NULL)
	{
		next = current->next;
		free_argv(current->argv);
		free_lexer(&current->lexer);
		free(current);
		current = next;
	}
	*cmd = NULL;
}

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	current = *env;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	*env = NULL;
}
