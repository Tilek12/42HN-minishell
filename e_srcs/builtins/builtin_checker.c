/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:43 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:20:57 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-----------------------------------------------------------*/
/*  Check if the argument equals to "cd" (case-insensitive)  */
/*-----------------------------------------------------------*/
int	is_cd(char *arg)
{
	if (arg == NULL || ft_strlen(arg) != 2)
		return (0);
	else
	{
		if (arg[0] != 'c' && arg[0] != 'C')
			return (0);
		if (arg[1] != 'd' && arg[1] != 'D')
			return (0);
	}
	return (1);
}

/*------------------------------------------------------------*/
/*  Check if the argument equals to "pwd" (case-insensitive)  */
/*------------------------------------------------------------*/
int	is_pwd(char *arg)
{
	if (arg == NULL || ft_strlen(arg) != 3)
		return (0);
	else
	{
		if (arg[0] != 'p' && arg[0] != 'P')
			return (0);
		if (arg[1] != 'w' && arg[1] != 'W')
			return (0);
		if (arg[2] != 'd' && arg[2] != 'D')
			return (0);
	}
	return (1);
}

/*------------------------------------------------------------*/
/*  Check if the argument equals to "env" (case-insensitive)  */
/*------------------------------------------------------------*/
int	is_env(char *arg)
{
	if (arg == NULL || ft_strlen(arg) != 3)
		return (0);
	else
	{
		if (arg[0] != 'e' && arg[0] != 'E')
			return (0);
		if (arg[1] != 'n' && arg[1] != 'N')
			return (0);
		if (arg[2] != 'v' && arg[2] != 'V')
			return (0);
	}
	return (1);
}

/*-------------------------------------------------------------*/
/*  Check if the argument equals to "echo" (case-insensitive)  */
/*-------------------------------------------------------------*/
int	is_echo(char *arg)
{
	if (arg == NULL || ft_strlen(arg) != 4)
		return (0);
	else
	{
		if (arg[0] != 'e' && arg[0] != 'E')
			return (0);
		if (arg[1] != 'c' && arg[1] != 'C')
			return (0);
		if (arg[2] != 'h' && arg[2] != 'H')
			return (0);
		if (arg[3] != 'o' && arg[3] != 'O')
			return (0);
	}
	return (1);
}

/*--------------------------------------------------------*/
/*  Check if the argument is one of the builtin commands  */
/*--------------------------------------------------------*/
int	is_builtin(char *arg)
{
	if (arg == NULL)
		return (0);
	else if (is_cd(arg))
		return (1);
	else if (is_pwd(arg))
		return (1);
	else if (is_env(arg))
		return (1);
	else if (is_echo(arg))
		return (1);
	else if (ft_strcmp(arg, "export") == 0)
		return (1);
	else if (ft_strcmp(arg, "unset") == 0)
		return (1);
	else if (ft_strcmp(arg, "exit") == 0)
		return (1);
	else
		return (0);
}
