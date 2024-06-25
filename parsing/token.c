/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:14:05 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/25 22:53:13 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		parsing(t_obj *obj);
int		quotes(char *str);
t_token	*tokenize(char **str);
char	*get_token(char **str);
void	token_type(t_token **token);

int	parsing(t_obj *obj)
{
	char	*str;

	str = obj->str;
	if (str == NULL)
		return (determine_exit_code(obj, SUCCESS));
	else if (quotes(str) == FAILURE)
		return (determine_exit_code(obj, Q_ERROR));
	obj->token = tokenize(&str);
	if (ft_syntax(obj->token) == FAILURE)
	{
		free_token(&obj->token);
		return (determine_exit_code(obj, SYNTAX_ERRROR));
	}
	expand(obj);
	obj->cmd = create_list(obj->token);
	free_token(&obj->token);
	return (determine_exit_code(obj, SUCCESS));
}

int	quotes(char *str)
{
	char	c;

	c = 0;
	skip_space(&str);
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			c = *str;
			str++;
			while (*str && *str != c)
				str++;
			if (*str == '\0')
			{
				printf("minishell: syntax error with open quotes\n");
				return (FAILURE);
			}
		}
		str++;
	}
	return (SUCCESS);
}

t_token	*tokenize(char **str)
{
	t_token	*token;
	char	*line;

	line = NULL;
	token = NULL;
	while (*(*str))
	{
		skip_space(str);
		line = get_token(str);
		append_token(&token, line);
		token_type(&token);
		free(line);
		if (*(*str) == '\0')
			break ;
		(*str)++;
		skip_space(str);
	}
	return (token);
}

char	*get_token(char **str)
{
	char	*line;
	int		i;
	char	c;

	i = 0;
	c = 0;
	line = (char *)malloc(alloc_mem(*str) + 1);
	if (!line)
		return (NULL);
	while (*(*str))
	{
		if (*(*str) == '\"' || *(*str) == '\'')
			c = set_char(str, c);
		line[i] = *(*str);
		i++;
		if (check_sep(str, c) != 0)
			break ;
		(*str)++;
	}
	line[i] = '\0';
	return (line);
}

void	token_type(t_token **token)
{
	t_token	*token_tmp;

	token_tmp = *token;
	while (token_tmp->next)
		token_tmp = token_tmp->next;
	if (ft_strcmp(token_tmp->str, "") == 0)
		token_tmp->type = EMPTY;
	else if (ft_strcmp(token_tmp->str, "|") == 0)
		token_tmp->type = PIPE;
	else if (ft_strcmp(token_tmp->str, ">") == 0)
		token_tmp->type = TRUNC;
	else if (ft_strcmp(token_tmp->str, "<") == 0)
		token_tmp->type = INPUT;
	else if (ft_strcmp(token_tmp->str, ">>") == 0)
		token_tmp->type = APPEND;
	else if (ft_strcmp(token_tmp->str, "<<") == 0)
		token_tmp->type = HEREDOC;
	else if (token_tmp->prev == NULL || token_tmp->prev->type == PIPE)
		token_tmp->type = COMMAND;
	else if (token_tmp->prev->prev && token_tmp->prev->prev->type == HEREDOC)
		token_tmp->type = COMMAND;
	else
		token_tmp->type = ARG;
}
