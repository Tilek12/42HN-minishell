/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:54:56 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/27 18:03:15 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*------------------------------------------*/
/*  Function to execute the "exit" command  */
/*------------------------------------------*/
void	execute_exit(t_data *data, char **args, int *exit_code)
{
	printf("exit\n");
	if (array_len(args) > 1)
	{
		if (is_number(args[1]))
		{
			if (array_len(args) == 2)
				free_exit(data, ft_atoi(args[1]));
			else
			{
				ft_perror("minishell: exit: too many arguments", NULL, NULL);
				*exit_code = 1;
				return ;
			}
		}
		else
		{
			ft_perror("minishell: exit: ", args[1],
				": numeric argument required");
			free_exit(data, 255);
		}
	}
	else
		free_exit(data, *exit_code);
}
