/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:19:19 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:52:44 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*---------------------------------------------------*/
/*  Find environment variable by name without value  */
/*---------------------------------------------------*/
int	env_var_find_no_value(char **env, const char *name)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

/*------------------------------------------------*/
/*  Find environment variable by name with value  */
/*------------------------------------------------*/
int	env_var_find(char **env, const char *name)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

/*------------------------------------------*/
/*  Create new environment variable string  */
/*------------------------------------------*/
char	*env_var_create(const char *name, const char *value)
{
	char	*new_env_var;
	char	*temp;

	if (value)
	{
		temp = ft_strjoin(name, "=");
		if (temp == NULL)
			return (NULL);
		new_env_var = ft_strjoin(temp, value);
		if (new_env_var == NULL)
			return (NULL);
		free(temp);
	}
	else
	{
		new_env_var = ft_strdup(name);
	}
	return (new_env_var);
}

/*---------------------------------------*/
/*  Add new variable to the environment  */
/*---------------------------------------*/
int	env_var_add(char ***env, char *new_env_var)
{
	int		env_len;
	char	**new_env;

	env_len = 0;
	while ((*env)[env_len])
		env_len++;
	new_env = my_realloc(*env, (env_len + 1) * sizeof(char *), \
							(env_len + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_env_var);
		return (-1);
	}
	new_env[env_len] = new_env_var;
	new_env[env_len + 1] = NULL;
	*env = new_env;
	return (0);
}

/*------------------------------------*/
/*  Remove variable from environment  */
/*------------------------------------*/
int	env_var_remove(char ***env, int index)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;

	len = env_len(*env);
	new_env = (char **)malloc(sizeof(char *) * len);
	if (!new_env)
		return (-1);
	i = -1;
	j = 0;
	while (++i < len)
	{
		if (i != index)
		{
			new_env[j] = (*env)[i];
			j++;
		}
		else
			free((*env)[i]);
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}
