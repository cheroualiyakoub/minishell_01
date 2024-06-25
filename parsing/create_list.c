/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:37 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 11:48:37 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	argv_len(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token && token->type <= 3)
		{
			count++;
		}
		else if (token && token->type > 3)
			token = token->next;
		token = token->next;
	}
	return (count);
}

void	ft_redirection(t_lexer **lexer, t_token **token)
{
	if ((*token) && (*token)->next)
	{
		append_lexer(lexer, (*token)->next->str, (*token)->type);
		(*token) = (*token)->next;
	}
}

t_cmd	*create_list(t_token *token)
{
	t_cmd	*cmd;
	t_lexer	*lexer;
	char	**argv;
	int		i;

	cmd = NULL;
	while (token)
	{
		lexer = NULL;
		argv = (char **)malloc(sizeof(char *) * (argv_len(token) + 1));
		argv[argv_len(token)] = NULL;
		i = 0;
		while (token && token->type != PIPE)
		{
			if (token && token->type <= 3)
				argv[i++] = ft_strdup(token->str);
			else if (token && token->type > 3)
				ft_redirection(&lexer, &token);
			token = token->next;
		}
		append_argv(&cmd, lexer, argv);
		if (token)
			token = token->next;
	}
	return (cmd);
}
