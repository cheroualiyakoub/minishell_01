/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:37 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/25 22:37:56 by ycheroua         ###   ########.fr       */
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

t_cmd	*creat_list_loop(t_token *token, t_cmd *cmd, \
			t_lexer *lexer, char **argv)
{
	int	i;

	while (token)
	{
		lexer = NULL;
		argv = (char **)malloc(sizeof(char *) * (argv_len(token) + 1));
		if (!argv)
			return (NULL);
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

t_cmd	*create_list(t_token *token)
{
	t_cmd	*cmd;
	t_lexer	*lexer;
	char	**argv;

	cmd = NULL;
	lexer = NULL;
	argv = NULL;
	return (creat_list_loop(token, cmd, lexer, argv));
}
