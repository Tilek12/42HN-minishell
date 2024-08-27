/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:05:44 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 21:06:41 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------------------------*/
/*  Check if the path leads to executable file  */
/*----------------------------------------------*/
int	is_executable(char *cmd_path)
{
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, R_OK) == 0)
		{
			if (access(cmd_path, X_OK) == 0)
				return (1);
		}
	}
	return (0);
}

/*--------------------------------------------*/
/*  Check if the external command is correct  */
/*--------------------------------------------*/
int	is_accessible(char *cmd_name, char **cmd_path, char **env)
{
	char	*path;
	char	**path_array;
	int		i;

	if (*cmd_path != NULL)
	{
		if (is_executable(*cmd_path))
			return (1);
		else
			return (-1);
	}
	path = env_value_get(env, "PATH");
	if (path == NULL)
		return (-1);
	path_array = split_str(path, ':');
	i = 0;
	while (path_array[i])
	{
		*cmd_path = my_strjoin(path_array[i], "/", cmd_name);
		if (is_executable(*cmd_path))
			return (free_array(path_array), 1);
		free(*cmd_path);
		i++;
	}
	return (free_array(path_array), 0);
}
