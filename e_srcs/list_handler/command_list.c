/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:17:37 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:28:47 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------------*/
/*  Count aguments of each command  */
/*----------------------------------*/
int	count_arguments(char **tokens, int index)
{
	int	counter;

	counter = 0;
	while (tokens[index] && ft_strncmp(tokens[index], "|", 1) != 0)
	{
		counter++;
		index++;
	}
	return (counter);
}

/*----------------------------------*/
/*  Count commands in tokens array  */
/*----------------------------------*/
int	count_commands(char **tokens)
{
	int	counter;
	int	i;

	counter = 1;
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
			counter++;
		i++;
	}
	return (counter);
}

/*--------------------------------------------------------*/
/*  Create 2D array of arguments in commands linked list  */
/*--------------------------------------------------------*/
char	**cmd_list_set_args(char **tokens, int len, int index)
{
	char	**cmd_args;
	int		i;

	cmd_args = (char **)malloc((len + 1) * sizeof(char *));
	if (cmd_args == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		cmd_args[i] = ft_strdup(tokens[index]);
		if (!cmd_args[i])
		{
			while (i > 0)
				free(cmd_args[--i]);
			free(cmd_args);
			return (NULL);
		}
		i++;
		index++;
	}
	cmd_args[i] = NULL;
	return (cmd_args);
}

/*--------------------------------------------------*/
/*  Create and add new node to command linked list  */
/*--------------------------------------------------*/
int	cmd_list_add_new(t_cmd **head, char **tokens, int len, int index)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (new_cmd == NULL)
		return (perror("malloc"), -1);
	new_cmd->args = cmd_list_set_args(tokens, len, index);
	new_cmd->args_num = len;
	new_cmd->is_heredoc = 0;
	new_cmd->is_redir_input = 0;
	new_cmd->is_redir_output = 0;
	new_cmd->heredoc_input = NULL;
	new_cmd->input_list = NULL;
	new_cmd->output_list = NULL;
	new_cmd->cmd_array = NULL;
	new_cmd->next = NULL;
	if (*head == NULL)
	{
		new_cmd->index = 0;
		*head = new_cmd;
	}
	else
		cmd_list_add(*head, new_cmd);
	return (0);
}

/*------------------------------*/
/*  Handle command linked list  */
/*------------------------------*/
void	cmd_list_handler(t_data *data)
{
	char	**tokens;
	int		args_num;
	int		cmds_num;
	int		i;

	if (data == NULL || data->tokens == NULL)
		return ;
	tokens = data->tokens;
	cmds_num = count_commands(tokens);
	data->cmd_num = cmds_num;
	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], "|", 1) == 0)
			i++;
		else
		{
			args_num = count_arguments(tokens, i);
			if (cmd_list_add_new(&data->cmd_list, tokens, args_num, i) == -1)
				free_exit(data, 1);
			i = i + args_num;
		}
	}
}
