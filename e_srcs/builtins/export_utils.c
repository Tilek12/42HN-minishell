/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:26:05 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:04:19 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*----------------------------*/
/*  Set environment variable  */
/*----------------------------*/
int	export_update_env(char ***env, const char *name, const char *value,
	int overwrite)
{
	int		i;
	char	*new_env_var;

	i = env_var_find(*env, name);
	new_env_var = env_var_create(name, value);
	if (!new_env_var)
		return (-1);
	if (i != -1)
	{
		if (overwrite)
		{
			free((*env)[i]);
			(*env)[i] = new_env_var;
		}
		else
			free(new_env_var);
		return (0);
	}
	return (env_var_add(env, new_env_var));
}

/*--------------------------------------------*/
/*  Check for valid input for export command  */
/*--------------------------------------------*/
int	is_valid_export_value(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL)
	{
		ft_perror("minishell: export: `': not a valid identifier", NULL, NULL);
		return (0);
	}
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_perror("minishell: export: `", arg, "': not a valid identifier");
		return (0);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			ft_perror("minishell: export: `", arg, "': not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}
