/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:09:08 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:47:43 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------------------------------------*/
/*  Update the value of underscore variable in environment  */
/*----------------------------------------------------------*/
void	update_underscore_var(t_data *data, char *value)
{
	char	*new_var;
	int		index;

	index = env_var_find(data->env, "_");
	if (index == -1)
	{
		new_var = env_var_create("_", value);
		if (env_var_add(&data->env, new_var) == -1)
			free_exit(data, 1);
	}
	else
		env_value_change(data->env, "_", value);
}

/*-------------------------------------------------*/
/*  Run child process for single extarnal command  */
/*-------------------------------------------------*/
void	fork_external(t_data *data, t_cmd *cmd)
{
	pid_t	pid;
	int		exit_status;

	update_underscore_var(data, array_last(cmd->cmd_array));
	pid = fork();
	if (pid == 0)
	{
		execute_external(data, cmd);
		free_exit(data, *data->exit_code);
	}
	else if (pid > 0)
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			*data->exit_code = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			*data->exit_code = WTERMSIG(exit_status) + 128;
	}
	else
		free_error_exit(data, 1, "fork");
}

/*-------------------------*/
/*  Set path command path  */
/*-------------------------*/
char	*set_cmd_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (str);
		i++;
	}
	return (NULL);
}

/*----------------------------------------------------------*/
/*  Print wrong command error message and change exit code  */
/*----------------------------------------------------------*/
void	print_wrong_command(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": command not found");
	*exit_code = 127;
}

/*-------------------------------------------------------*/
/*  Print wrong path error message and change exit code  */
/*-------------------------------------------------------*/
void	print_wrong_path(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": No such file or directory");
	*exit_code = 127;
}
