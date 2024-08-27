/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:25:36 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:18:23 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------------*/
/*  Count redirections in 2D array  */
/*----------------------------------*/
int	redir_count(char **args)
{
	int	redir_counter;
	int	i;

	redir_counter = 0;
	i = 0;
	while (args[i])
	{
		if (is_redirection(args[i]))
			redir_counter++;
		i++;
	}
	return (redir_counter);
}

/*---------------------------------------------*/
/*  Find last node in redirection linked list  */
/*---------------------------------------------*/
t_redir	*redir_list_last(t_redir *head)
{
	t_redir	*last;

	if (head == NULL)
		return (NULL);
	last = head;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

/*-------------------------------------------*/
/*  Add new node to redirection linked list  */
/*-------------------------------------------*/
void	redir_list_add(t_redir *head, t_redir *new)
{
	t_redir	*current;

	if (head == NULL || new == NULL)
		return ;
	else
	{
		current = redir_list_last(head);
		current->next = new;
	}
}

/*------------------------------------------------*/
/*  Save every command argument in command array  */
/*------------------------------------------------*/
void	cmd_array_handler(char **args, int *counter, char **cmd_array, \
							t_status status)
{
	int		skip;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (args[i])
	{
		if (is_redirection(args[i]))
		{
			if (!is_redirection(args[i + 1]) || args[i + 1] != NULL)
				skip = 2;
			else
				skip = 1;
		}
		else
		{
			if (status == COUNT)
				(*counter)++;
			else if (status == SET)
				cmd_array[j++] = ft_strdup(args[i]);
			skip = 1;
		}
		i = i + skip;
	}
}

/*-------------------------------------------------*/
/*  Create 2D array for command and its arguments  */
/*-------------------------------------------------*/
int	set_cmd_array(t_cmd *cmd)
{
	int	cmd_counter;

	cmd_counter = 0;
	cmd_array_handler(cmd->args, &cmd_counter, NULL, COUNT);
	if (cmd_counter == 0)
	{
		cmd->cmd_array = (char **)malloc(sizeof(char *));
		if (cmd->cmd_array == NULL)
			return (perror("malloc"), -1);
		cmd->cmd_array[0] = NULL;
	}
	else
	{
		cmd->cmd_array = (char **)malloc((cmd_counter + 1) * sizeof(char *));
		if (cmd->cmd_array == NULL)
			return (perror("malloc"), -1);
		cmd->cmd_array[cmd_counter] = NULL;
		cmd_array_handler(cmd->args, NULL, cmd->cmd_array, SET);
	}
	return (0);
}
