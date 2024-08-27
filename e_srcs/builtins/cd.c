/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:51 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 17:59:52 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------*/
/*  Change current directory  */
/*----------------------------*/
int	change_directory(char *path, int *exit_code)
{
	if (ft_strncmp(path, "~", 1) == 0)
	{
		if (cd_expand_tilde(&path) == -1)
		{
			*exit_code = 1;
			return (-1);
		}
		if (cd_error_catcher(path) == 0)
		{
			free(path);
			*exit_code = 1;
			return (0);
		}
		free(path);
	}
	else
	{
		if (cd_error_catcher(path) == 0)
		{
			*exit_code = 1;
			return (0);
		}
	}
	*exit_code = 0;
	return (1);
}

/*------------------------------------*/
/*  Change current directory to home  */
/*------------------------------------*/
int	cd_home_dir(char **env, int *exit_code)
{
	char	*home;

	home = env_value_get(env, "HOME");
	if (!home)
	{
		ft_perror("minishell: cd: HOME not set", NULL, NULL);
		*exit_code = 1;
		return (0);
	}
	return (change_directory(home, exit_code));
}

/*--------------------------------------------*/
/*  Change current directory to previous one  */
/*--------------------------------------------*/
int	cd_dash_arg(char **env, int *exit_code)
{
	char	*prev_dir;

	prev_dir = env_value_get(env, "OLDPWD");
	if (!prev_dir)
	{
		ft_perror("minishell: cd: OLDPWD not set", NULL, NULL);
		*exit_code = 1;
		return (0);
	}
	printf("%s\n", prev_dir);
	return (change_directory(prev_dir, exit_code));
}

/*------------------------------------------*/
/*  Function to execute the "echo" command  */
/*------------------------------------------*/
int	execute_cd(char **args, char ***env, int *exit_code)
{
	char	curr_dir[PATH_MAX];
	int		result;

	result = 0;
	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return (-1);
	}
	if (array_len(args) == 1)
		result = cd_home_dir(*env, exit_code);
	else if (ft_strncmp(args[1], "-", 1) == 0 && ft_strlen(args[1]) == 1)
		result = cd_dash_arg(*env, exit_code);
	else
		result = change_directory(args[1], exit_code);
	if (result == 1)
		return (env_value_change_pwd_oldpwd(curr_dir, env, exit_code));
	else
		return (result);
}
