/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:03:24 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:53:51 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------------------------------*/
/*  Wait for all child processes and catch exit code  */
/*  from last child process (aka command)             */
/*----------------------------------------------------*/
void	wait_processes(pid_t last_pid, int *last_exit_code)
{
	pid_t	pid;
	int		exit_status;

	pid = wait(&exit_status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(exit_status))
				*last_exit_code = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				*last_exit_code = WTERMSIG(exit_status) + 128;
		}
		pid = wait(&exit_status);
	}
}

/*-------------------------------------------*/
/*  Close all file descriptors of all pipes  */
/*-------------------------------------------*/
void	pipe_close_all(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if (current->pipe_fd[0] != -1)
			close(current->pipe_fd[0]);
		if (current->pipe_fd[1] != -1)
			close(current->pipe_fd[1]);
		current = current->next;
	}
}

/*---------------------------------------------------------*/
/*  Handle file descriptors of pipes between each command  */
/*---------------------------------------------------------*/
void	pipe_redirection_handler(t_data *data, t_cmd *curr_cmd)
{
	int		prev_index;
	t_cmd	*cmd_list;
	t_cmd	*prev_cmd;

	cmd_list = data->cmd_list;
	prev_index = curr_cmd->index - 1;
	prev_cmd = cmd_list_find(cmd_list, prev_index);
	if (prev_cmd != NULL)
	{
		if (dup2(prev_cmd->pipe_fd[0], STDIN_FILENO) == -1)
			free_error_exit(data, *data->exit_code, "dup2");
	}
	if (curr_cmd->next != NULL)
	{
		if (dup2(curr_cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			free_error_exit(data, *data->exit_code, "dup2");
	}
	pipe_close_all(cmd_list);
}

/*----------------------------------------------*/
/*  Create pipes for every command in pipeline  */
/*----------------------------------------------*/
int	pipe_set_all(t_cmd *cmd_list)
{
	t_cmd	*current;

	current = cmd_list;
	while (current)
	{
		if (current->next == NULL)
		{
			current->pipe_fd[0] = -1;
			current->pipe_fd[1] = -1;
		}
		else
		{
			if (pipe(current->pipe_fd) == -1)
			{
				perror("pipe");
				return (-1);
			}
		}
		current = current->next;
	}
	return (0);
}
