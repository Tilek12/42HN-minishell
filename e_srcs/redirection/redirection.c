/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:33:40 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 19:04:52 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-----------------------*/
/*  Get input from file  */
/*-----------------------*/
int	redir_input_file(t_redir *redir, int *exit_code)
{
	int	fd;

	fd = open(redir->name, O_RDONLY);
	if (fd == -1)
	{
		ft_perror("minishell: ", redir->name, ": No such file or directory");
		*exit_code = 1;
		return (0);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (1);
}

/*--------------------------*/
/*  Get input from heredoc  */
/*--------------------------*/
int	redir_input_heredoc(char *heredoc_input)
{
	int	pipe_fd[2];

	if (heredoc_input == NULL)
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (write(pipe_fd[1], heredoc_input, ft_strlen(heredoc_input)) == -1)
		return (-1);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		perror("dup2");
		return (-1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (1);
}

/*----------------------------*/
/*  Handle input redirection  */
/*----------------------------*/
int	redir_input_handler(t_redir *input_list, char *heredoc_input, \
							int *exit_code)
{
	int		result;
	t_redir	*current;

	result = 1;
	current = input_list;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (current->next == NULL)
				return (redir_input_heredoc(heredoc_input));
			else
				current = current->next;
		}
		else if (current->type == INPUT)
		{
			result = redir_input_file(current, exit_code);
			if (result == 0 || result == -1)
				return (result);
			current = current->next;
		}
	}
	return (result);
}

/*-----------------------------*/
/*  Handle output redirection  */
/*-----------------------------*/
int	redir_output_handler(t_redir *output_list, int *exit_code)
{
	t_redir	*current;
	int		fd;

	current = output_list;
	while (current)
	{
		if (current->type == APPEND)
			fd = open(current->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (current->type == OUTPUT)
			fd = open(current->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			*exit_code = 1;
			return (perror("open"), 0);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			perror("dup2");
			return (-1);
		}
		close(fd);
		current = current->next;
	}
	return (1);
}

/*------------------------*/
/*  Handling redirection  */
/*------------------------*/
int	redirection_handler(t_cmd *cmd, int *exit_code)
{
	int		result;
	t_redir	*input_list;
	t_redir	*output_list;
	char	*heredoc_input;

	result = 1;
	input_list = cmd->input_list;
	output_list = cmd->output_list;
	heredoc_input = cmd->heredoc_input;
	if (cmd->is_redir_input && input_list)
	{
		result = redir_input_handler(input_list, heredoc_input, exit_code);
		if (result == -1 || result == 0)
			return (result);
	}
	if (cmd->is_redir_output && output_list)
		result = redir_output_handler(output_list, exit_code);
	return (result);
}
