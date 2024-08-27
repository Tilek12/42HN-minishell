/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:24:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:02:08 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-------------------------------------------------------*/
/*  Function to check if all characters is equal to "n"  */
/*-------------------------------------------------------*/
int	echo_is_all_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	if (ft_strlen(arg) == 1)
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/*--------------------------------*/
/*  Function to skip "-n" option  */
/*--------------------------------*/
int	echo_skip_all_n(char **args, int *i)
{
	int	all_n;

	all_n = 0;
	while (args[*i] && echo_is_all_n(args[*i]))
	{
		all_n = 1;
		(*i)++;
	}
	return (all_n);
}

/*------------------------------------------*/
/*  Function to execute the "echo" command  */
/*------------------------------------------*/
int	execute_echo(char **args, int *exit_code)
{
	int		new_line;
	int		space;
	int		i;

	new_line = 1;
	space = 0;
	i = 1;
	if (echo_skip_all_n(args, &i))
		new_line = 0;
	while (args[i])
	{
		if (space)
			printf(" ");
		printf("%s", args[i]);
		space = 1;
		i++;
	}
	if (new_line)
		printf("\n");
	*exit_code = 0;
	return (0);
}
