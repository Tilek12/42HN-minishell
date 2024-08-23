/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:21 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/22 19:49:56 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_redir_list(t_redir **head)
{
	t_redir	*current;
	t_redir	*next;

	if (*head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		if (current->name != NULL)
			free(current->name);
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_cmd_list(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next;

	if (*head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		free_array(current->args);
		free_array(current->cmd_array);
		free_redir_list(&current->heredoc_list);
		free_redir_list(&current->input_list);
		free_redir_list(&current->output_list);
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void	free_exit(t_data *data, int exit_code)
{
	if (data == NULL)
		return ;
	free_array(data->env);
	data->env = NULL;
	free_array(data->tokens);
	data->tokens = NULL;
	free_cmd_list(&data->cmd_list);
	exit(exit_code);
}

void	free_error_exit(t_data *data, int exit_code, char *error_msg)
{
	if (error_msg != NULL)
		perror(error_msg);
	free_exit(data, exit_code);
}
