/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:28:40 by ycheroua          #+#    #+#             */
/*   Updated: 2024/06/25 22:29:36 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process_execution(t_obj *obj, \
			char *full_path, t_cmd *curr_cmd, char **env)
{
	if (access(curr_cmd->argv[0], X_OK) == 0)
		full_path = curr_cmd->argv[0];
	else
	{
		full_path = pp_get_path_env(obj, curr_cmd->argv[0]);
		if (full_path == NULL)
		{
			perror("Command not found");
			exit(determine_exit_code(obj, Q_ERROR));
		}
	}
	execve(full_path, curr_cmd->argv, env);
	determine_exit_code(obj, Q_ERROR);
	perror("execve err");
	free(full_path);
	exit(determine_exit_code(obj, Q_ERROR));
}

void	child_porcess(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2], char **env)
{
	char	*full_path;

	full_path = NULL;
	if (curr_cmd->next != NULL)
	{
		dup2_error(obj, dup2(fd_pipe[1], STDOUT_FILENO));
		close_fds(fd_pipe[0], fd_pipe[1]);
	}
	if (set_redirections(curr_cmd) == Q_ERROR)
		exit(determine_exit_code(obj, Q_ERROR));
	if (curr_cmd->argv[0] && check_buildings(curr_cmd->argv))
		run_buildings(obj, curr_cmd->argv);
	else
	{
		child_process_execution(obj, full_path, curr_cmd, env);
	}
	exit(determine_exit_code(obj, Q_ERROR));
}

void	parent_process(t_obj *obj, t_cmd *curr_cmd, int fd_pipe[2])
{
	if (curr_cmd->next == NULL)
		close_fds(STDIN_FILENO, -1);
	else
	{
		dup2_error(obj, dup2(fd_pipe[0], STDIN_FILENO));
		close_fds(fd_pipe[1], fd_pipe[0]);
	}
}

void	execution_loop(t_obj *obj, int main_fd_in, int main_fd_out, char **env)
{
	t_cmd	*curr_cmd;
	int		pid;
	int		fd_pipe[2];

	curr_cmd = obj->cmd;
	pid = 0;
	obj->pid = malloc(sizeof(int) * count_cmds(obj));
	while (curr_cmd)
	{
		pipe_error(obj, pipe(fd_pipe));
		obj->pid[pid] = fork_erro(obj, fork());
		if (obj->pid[pid] == 0)
		{
			close(main_fd_in);
			close(main_fd_out);
			child_porcess(obj, curr_cmd, fd_pipe, env);
		}
		else
		{
			parent_process(obj, curr_cmd, fd_pipe);
			curr_cmd = curr_cmd->next;
			pid++;
		}
	}
}

int	executor(t_obj *obj, char **env)
{
	int		status;
	t_cmd	*curr_cmd;
	int		std_in;
	int		std_out;

	std_in = dup_error(obj, dup(STDIN_FILENO));
	std_out = dup_error(obj, dup(STDOUT_FILENO));
	curr_cmd = obj->cmd;
	ft_heredoc(obj);
	if (curr_cmd && curr_cmd->argv[0] && check_buildings(curr_cmd->argv) \
		&& curr_cmd->next == NULL)
	{
		if (set_redirections(curr_cmd) == Q_ERROR)
			return (determine_exit_code(obj, Q_ERROR), Q_ERROR);
		run_buildings(obj, curr_cmd->argv);
	}
	else if (curr_cmd && curr_cmd->argv[0])
	{
		execution_loop(obj, std_in, std_out, env);
		ft_wait_all(obj, &status);
	}
	dup2_error(obj, dup2(std_in, STDIN_FILENO));
	dup2_error(obj, dup2(std_out, STDOUT_FILENO));
	close_fds(std_in, std_out);
	return (Q_ERROR);
}
