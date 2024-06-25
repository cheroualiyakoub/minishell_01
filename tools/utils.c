/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:19:00 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/24 12:57:27 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] == ' ' || str[i] == '?')
			return (-1);
		i++;
	}
	if (str[i] == '\0')
		return (0);
	return (i);
}

int	check_sep(char **str, char c)
{
	if (c != 0)
		return (0);
	else if ((*(*str) == '>' || *(*str) == '<'))
	{
		if (*(*str + 1) == *(*str))
			return (0);
		return (1);
	}
	else if ((*(*str) == ' ' || *(*str) == '|'))
		return (1);
	else if ((*(*str + 1) == ' ' || *(*str + 1) == '|' \
			|| *(*str + 1) == '>' || *(*str + 1) == '<'))
		return (1);
	return (0);
}

void	skip_space(char **str)
{
	while (*(*str) == ' ' || *(*str) == '\t' \
		|| *(*str) == '\r' || *(*str) == '\v' || *(*str) == '\f')
		(*str)++;
}

int	check_redirection(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && (!token->next || !token->prev))
			return (-2);
		if ((token->type == APPEND || token->type == INPUT \
				|| token->type == TRUNC \
				|| token->type == HEREDOC) && (!token->next || \
			token->next->type > ARG))
			return (-3);
		else if ((ft_strchr(token->str, '\"') == NULL && \
				ft_strchr(token->str, '\'') == NULL) && \
				(ft_strnstr(token->str, ">>>", ft_strlen(token->str)) \
				|| ft_strnstr(token->str, "<<<", ft_strlen(token->str))))
			return (-4);
		token = token->next;
	}
	return (SUCCESS);
}

int	ft_syntax(t_token *token)
{
	int	n;

	n = check_redirection(token);
	if (n != 0)
	{
		if (n == -2)
			printf("bash: syntax error near unexpected token `|'\n");
		else if (n == -3)
			printf("bash: syntax error near unexpected token `newline'\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
