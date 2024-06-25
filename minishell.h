/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:03:55 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/25 22:49:11 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>

# include "libft/libft.h"

# define SUCCESS 0
# define FAILURE -1
# define Q_ERROR 130
# define SYNTAX_ERRROR 1

# define EMPTY 0
# define COMMAND 1
# define ARG 3
# define APPEND 4 // >>
# define INPUT 5 // <
# define TRUNC 6 // >
# define HEREDOC 7 // <<
# define PIPE 8 // |

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	char			*str;
	int				i;
	struct s_lexer	*next;
}	t_lexer;

typedef struct t_cmd
{
	char			**argv;
	t_lexer			*lexer;
	struct t_cmd	*next;
	struct t_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_tool
{
	char	*pwd;
	char	*oldpwd;
}	t_tool;

typedef struct s_obj
{
	t_token	*token;
	t_cmd	*cmd;
	t_env	*env;
	t_tool	tool;
	char	*str;
	int		*pid;
	int		exit_code;
}	t_obj;

typedef struct s_bulding
{
	char	*str;
	int		(*function)(char **argv, t_obj *obj);
}	t_bulding;

//signal
void	init_signal(void);

// parsing
int		parsing(t_obj *obj);
int		quotes(char *str);
t_token	*tokenize(char **str);
char	*get_token(char **str);
void	token_type(t_token **token);
char	set_char(char **str, char c);

// expand the tokens
void	expand(t_obj *obj);
char	*get_value(t_obj *obj, char *str);
char	*no_quotes(t_obj *obj, char **argv, int *i);
char	*do_quotes(t_obj *obj, char **argv, int *i);
char	*si_quotes(char **argv, int *i);

//create list from expanded tokens.c
t_cmd	*create_list(t_token *token);
int		argv_len(t_token *token);

//heredoc
int		ft_heredoc(t_obj *obj);

//utils.c
int		check_equal(char *str);
int		ft_syntax(t_token *token);
void	skip_space(char **str);
int		check_sep(char **str, char c);
int		check_equal(char *str);

//append.c
int		alloc_mem(char *str);
void	append_env(t_env **token, char *str);
void	append_token(t_token **token, char *str);
void	append_lexer(t_lexer **lexer, char *str, int i);
void	append_argv(t_cmd **cmd, t_lexer *lexer, char **argv);

// all function to free dynamic memory
void	free_argv(char **argv);
void	free_token(t_token **token);
void	free_cmd(t_cmd **cmd);
void	free_env(t_env **env);

//buildin
int		ft_echo(char **argv, t_obj *obj);
int		ft_pwd(char **argv, t_obj *obj);
int		ft_export(char **argv, t_obj *obj);
int		ft_unset(char **argv, t_obj *obj);
int		ft_env(char **argv, t_obj *obj);
int		ft_cd(char **argv, t_obj *obj);
int		ft_exit(char **argv, t_obj *obj);

//utils and tools for buildin functions
int		run_buildings(t_obj *obj, char **argv);
int		check_buildings(char **argv);
void	add_env(char *str, t_env **env);
int		determine_exit_code(t_obj *obj, int n);

//execute
int		executor(t_obj *obj, char **env);
int		pipex_excutor(t_obj *obj, int count_cmds);
char	**ft_split_simple(char const *str, char charset);
int		set_redirections(t_cmd *cmd);
char	*check_full_path(char *path_elemt, char *cmd);
char	*get_full_path(char **env_path, char *cmd);
char	*pp_get_path_env(t_obj *obj, char *cmd);
char	*pp_check_full_path(char *path_elemt, char *cmd);
void	pipe_error(t_obj *obj, int pid);
void	dup2_error(t_obj *obj, int dup);
void	fork_check(t_obj *obj, int pid);
int		dup_error(t_obj *obj, int dup);
int		fork_erro(t_obj *obj, int pid);
// void	ft_wait_all(t_obj *obj);
int		count_cmds(t_obj *obj);
void	close_fds(int fd1, int fd2);
void	ft_wait_all(t_obj *obj, int *status);

#endif
