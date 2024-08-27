/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:39:28 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:08:59 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-------------------------------------------*/
/*  Check for valid input for unset command  */
/*-------------------------------------------*/
int	is_valid_unset_value(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
	{
		ft_perror("minishell: unset: `': not a valid identifier", NULL, NULL);
		return (0);
	}
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_perror("minishell: unset: `", arg, "': not a valid identifier");
		return (0);
	}
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_perror("minishell: unset: `", arg, "': not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

/*----------------------------------------------*/
/*  Remove varibale from environment if exists  */
/*----------------------------------------------*/
int	unset_var_from_env(char *arg, char ***env)
{
	int	i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, ft_strlen(arg)) == 0)
		{
			if (env_var_remove(env, i) == -1)
			{
				perror("malloc");
				return (-1);
			}
			break ;
		}
		i++;
	}
	return (0);
}

/*-------------------------------------------*/
/*  Function to execute the "unset" command  */
/*-------------------------------------------*/
int	execute_unset(char **args, char ***env, int *exit_code)
{
	int	i;

	i = 1;
	if (array_len(args) == 1 || env == NULL || env[0] == NULL)
		return (1);
	*exit_code = 0;
	while (args[i])
	{
		if (!is_valid_unset_value(args[i]))
			*exit_code = 1;
		else
		{
			if (unset_var_from_env(args[i], env) == -1)
			{
				*exit_code = 1;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
