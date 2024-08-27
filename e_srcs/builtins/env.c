/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:17:14 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:02:45 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-----------------------------------------*/
/*  Function to execute the "env" command  */
/*-----------------------------------------*/
int	execute_env(char **env, int *exit_code)
{
	int		i;
	char	*equal_sign;

	if (env == NULL || env[0] == NULL)
		return (1);
	i = 0;
	while (env[i])
	{
		equal_sign = ft_strchr(env[i], '=');
		if (equal_sign)
			printf("%s\n", env[i]);
		i++;
	}
	*exit_code = 0;
	return (0);
}
