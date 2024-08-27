/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:26:13 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:06:48 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------------------*/
/*  Handle export argument with no value  */
/*----------------------------------------*/
int	export_arg_no_value(char *arg, char ***env)
{
	char	*name;

	name = arg;
	if (env_var_find(*env, name) == -1)
	{
		if (export_update_env(env, name, NULL, 0) == -1)
		{
			perror("malloc");
			return (-1);
		}
	}
	return (0);
}

/*-------------------------------------*/
/*  Handle export argument with value  */
/*-------------------------------------*/
int	export_arg_with_value(char *arg, char *equal_sign, char ***env)
{
	char	*name;
	char	*value;

	name = my_strndup(arg, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	if (name && value)
	{
		if (export_update_env(env, name, value, 1) != 0)
		{
			perror("malloc");
			return (-1);
		}
	}
	else
	{
		perror("malloc");
		return (-1);
	}
	free(name);
	free(value);
	return (0);
}

/*----------------------------------------*/
/*  Handle export command with arguments  */
/*----------------------------------------*/
int	export_with_args(char *arg, char ***env)
{
	int		result;
	char	*equal_sign;

	result = 0;
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		result = export_arg_with_value(arg, equal_sign, env);
	else
		result = export_arg_no_value(arg, env);
	if (result == -1)
		return (-1);
	return (0);
}

/*-------------------------------------------*/
/*  Handle export command with no arguments  */
/*-------------------------------------------*/
int	export_no_args(char **env, int *exit_code)
{
	char	**sorted_env;
	int		i;
	char	*equal_sign;

	sorted_env = env_sort(env);
	if (!sorted_env)
	{
		perror("malloc");
		*exit_code = 1;
		return (-1);
	}
	i = -1;
	while (sorted_env[++i])
	{
		equal_sign = ft_strchr(sorted_env[i], '=');
		if (equal_sign)
			printf("declare -x %.*s=\"%s\"\n",
				(int)(equal_sign - sorted_env[i]), sorted_env[i],
				equal_sign + 1);
		else
			printf("declare -x %s\n", sorted_env[i]);
	}
	free_array(sorted_env);
	*exit_code = 0;
	return (0);
}

/*------------------------------------------*/
/*  Main export command execution function  */
/*------------------------------------------*/
int	execute_export(char **args, char ***env, int *exit_code)
{
	int	result;
	int	i;

	if (array_len(args) == 1)
		result = export_no_args(*env, exit_code);
	*exit_code = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_export_value(args[i]))
			*exit_code = 1;
		else
		{
			result = export_with_args(args[i], env);
			if (result == -1)
			{
				*exit_code = 1;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
