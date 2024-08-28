/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 16:36:26 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/28 12:10:27 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------*/
/*  Save heredoc input  */
/*----------------------*/
int	heredoc_save_input(t_cmd *cmd, char *line)
{
	char	*temp;

	if (cmd == NULL || line == NULL)
		return (0);
	if (cmd->heredoc_input == NULL)
		cmd->heredoc_input = ft_strjoin(line, "\n");
	else
	{
		temp = my_strjoin(cmd->heredoc_input, line, "\n");
		if (temp == NULL)
			free(cmd->heredoc_input);
		free(cmd->heredoc_input);
		cmd->heredoc_input = temp;
	}
	return (0);
}

/*---------------------*/
/*  Get heredoc input  */
/*---------------------*/
int	heredoc_readline(t_cmd *cmd, char *delimeter, t_status status, t_data *data)
{
	char	*line;

	_handle_signals(INIT);
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		expand_heredoc(&line, data->env, data);
		if (ft_strcmp(line, delimeter) == 0)
		{
			free(line);
			break ;
		}
		if (status == SAVE)
		{
			if (heredoc_save_input(cmd, line) == -1)
				break ;
		}
		free(line);
	}
	return (0);
}

/*--------------------*/
/*  Run all heredocs  */
/*--------------------*/
void	heredoc_input_handler(t_data *data, t_cmd *cmd)
{
	t_redir	*current;
	char	*delimeter;

	current = cmd->input_list;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			delimeter = current->name;
			if (current->next != NULL)
			{
				if (heredoc_readline(cmd, delimeter, SKIP, data) == -1)
					free_exit(data, 1);
			}
			else
			{
				if (heredoc_readline(cmd, delimeter, SAVE, data) == -1)
					free_exit(data, 1);
			}
		}
		current = current->next;
	}
}

/*--------------------*/
/*  Handling heredoc  */
/*--------------------*/
void	heredoc_handler(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_list;
	while (current != NULL)
	{
		if (current->is_heredoc == 1)
			heredoc_input_handler(data, current);
		current = current->next;
	}
}
