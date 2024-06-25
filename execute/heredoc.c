/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashirzad <ashirzad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 11:23:59 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/24 14:34:07 by ashirzad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_heredoc(t_cmd *cmd)
{
	t_lexer	*lexer;

	lexer = NULL;
	while (cmd)
	{
		lexer = cmd->lexer;
		while (lexer)
		{
			if (lexer->i == HEREDOC)
				return (1);
			lexer = lexer->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

char	*ft_expand(t_obj *obj, char *str)
{
	char	**argv;
	int		i;

	i = 0;
	if (str == NULL || ft_strcmp(str, "") == 0)
		return (ft_strdup(""));
	argv = ft_split(str, ' ');
	free(str);
	str = NULL;
	while (argv[i])
	{
		if (ft_strrchr(argv[i], '$'))
			str = ft_strjoin2(str, get_value(obj, argv[i] + 1), 2);
		else
			str = ft_strjoin2(str, argv[i], 2);
		i++;
	}
	return (str);
}

char	*ft_run(t_obj *obj, char *stop, int n)
{
	char	*str;
	char	*file;
	int		fd;

	file = ft_strjoin2("f", ft_itoa(n), 3);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	while (1)
	{
		str = readline("> ");
		if (ft_strcmp(str, stop) == 0)
		{
			free(str);
			close(fd);
			break ;
		}
		str = ft_expand(obj, str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	return (file);
}

int	ft_heredoc(t_obj *obj)
{
	t_cmd	*cmd_t;
	t_lexer	*lexer;
	int		i;
	char	*name;

	i = 0;
	cmd_t = obj->cmd;
	lexer = NULL;
	if (is_heredoc(cmd_t) != 1)
		return (SUCCESS);
	while (cmd_t)
	{
		name = NULL;
		lexer = cmd_t->lexer;
		while (lexer)
		{
			if (lexer->i == HEREDOC)
			{
				name = ft_run(obj, lexer->str, i);
				free(lexer->str);
				lexer->str = NULL;
				lexer->str = ft_strdup(name);
				free(name);
				i++;
			}
			lexer = lexer->next;
		}
		cmd_t = cmd_t->next;
	}
	return (SUCCESS);
}
