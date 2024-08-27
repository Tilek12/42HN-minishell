/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:55:15 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:12:41 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*------------------------------------------------------*/
/*  Create and add new node to redirection linked list  */
/*------------------------------------------------------*/
int	new_redir_create(t_redir **redir_list, char *name, t_type type)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (new_redir == NULL)
		return (perror("malloc"), -1);
	new_redir->type = type;
	if (name == NULL)
		new_redir->name = NULL;
	else
		new_redir->name = ft_strdup(name);
	new_redir->next = NULL;
	if (*redir_list == NULL)
		*redir_list = new_redir;
	else
		redir_list_add(*redir_list, new_redir);
	return (0);
}

/*-------------------------------------------------------*/
/*  Define redirection type and redirection linked list  */
/*-------------------------------------------------------*/
int	new_redir_handler(t_cmd *cmd, char *name, t_type type)
{
	int	result;

	result = 0;
	if (type == HEREDOC)
	{
		cmd->is_heredoc = 1;
		cmd->is_redir_input = 1;
		result = new_redir_create(&cmd->input_list, name, type);
	}
	else if (type == INPUT)
	{
		cmd->is_redir_input = 1;
		result = new_redir_create(&cmd->input_list, name, type);
	}
	else if (type == APPEND)
	{
		cmd->is_redir_output = 1;
		result = new_redir_create(&cmd->output_list, name, type);
	}
	else if (type == OUTPUT)
	{
		cmd->is_redir_output = 1;
		result = new_redir_create(&cmd->output_list, name, type);
	}
	return (result);
}

/*-------------------------------------------------------*/
/*  Handle creating new node in redirection linked list  */
/*-------------------------------------------------------*/
int	redir_create(t_cmd *cmd, int index, t_type type)
{
	char	*name;
	int		result;

	result = 0;
	if (!is_redirection(cmd->args[index + 1]) || cmd->args[index + 1] != NULL)
		name = cmd->args[index + 1];
	else
		name = NULL;
	if (type == HEREDOC)
		result = new_redir_handler(cmd, name, HEREDOC);
	else if (type == INPUT)
		result = new_redir_handler(cmd, name, INPUT);
	else if (type == APPEND)
		result = new_redir_handler(cmd, name, APPEND);
	else if (type == OUTPUT)
		result = new_redir_handler(cmd, name, OUTPUT);
	if (result == -1)
		return (-1);
	if (name == NULL)
		return (1);
	else
		return (2);
}

/*-------------------------*/
/*  Check for redirection  */
/*-------------------------*/
int	redir_check(t_cmd *cmd)
{
	int		i;
	int		args_skip;
	int		redir_num;

	redir_num = redir_count(cmd->args);
	if (redir_num == 0)
		return (0);
	i = 0;
	while (cmd->args[i])
	{
		args_skip = 1;
		if (is_heredoc(cmd->args[i]))
			args_skip = redir_create(cmd, i, HEREDOC);
		else if (is_redir_input(cmd->args[i]))
			args_skip = redir_create(cmd, i, INPUT);
		else if (is_redir_append(cmd->args[i]))
			args_skip = redir_create(cmd, i, APPEND);
		else if (is_redir_otput(cmd->args[i]))
			args_skip = redir_create(cmd, i, OUTPUT);
		if (args_skip == -1)
			return (-1);
		else
			i = i + args_skip;
	}
	return (1);
}

/*----------------------------------*/
/*  Handle redirection linked list  */
/*----------------------------------*/
void	redir_list_handler(t_data *data)
{
	t_cmd	*current;
	int		result;

	if (data == NULL || data->cmd_list == NULL)
		return ;
	current = data->cmd_list;
	while (current != NULL)
	{
		result = redir_check(current);
		if (result == -1)
			free_exit(data, 1);
		else if (result == 0)
		{
			current->cmd_array = array_copy(current->args);
			if (current->cmd_array == NULL)
				free_exit(data, 1);
		}
		else if (result == 1)
		{
			if (set_cmd_array(current) == -1)
				free_exit(data, 1);
		}
		current = current->next;
	}
}
