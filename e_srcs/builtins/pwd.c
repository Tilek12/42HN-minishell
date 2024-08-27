/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:18:11 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:09:02 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-----------------------------------------*/
/*  Function to execute the "pwd" command  */
/*-----------------------------------------*/
int	execute_pwd(int *exit_code)
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return (-1);
	}
	printf("%s\n", curr_dir);
	*exit_code = 0;
	return (0);
}
