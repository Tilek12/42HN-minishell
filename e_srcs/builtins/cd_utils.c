/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 23:18:41 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 17:36:33 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*---------------------------*/
/*  Set home directory path  */
/*---------------------------*/
char	*set_home(void)
{
	char	path[PATH_MAX];
	char	*home;
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	if (getcwd(path, sizeof(path)) == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	while (path[i])
	{
		if (path[i] == '/')
			counter++;
		if (counter == 3)
			break ;
		i++;
	}
	home = my_strndup(path, i);
	return (home);
}

/*------------------------------------------------*/
/*  Expand tilde sign "~" to home directory path  */
/*------------------------------------------------*/
int	cd_expand_tilde(char **path)
{
	char	*home;
	char	*temp;
	int		path_len;

	path_len = ft_strlen(*path);
	if (path_len > 1)
	{
		temp = set_home();
		if (temp == NULL)
			return (-1);
		home = ft_strjoin(temp, *path + 1);
		if (home == NULL)
			return (free(temp), -1);
		free(temp);
	}
	else
	{
		home = set_home();
		if (home == NULL)
			return (-1);
	}
	*path = home;
	return (1);
}

/*--------------------------------------------*/
/*  Catch error type and print error message  */
/*--------------------------------------------*/
int	cd_error_catcher(char *path)
{
	struct stat	sb;
	int			result;

	if (access(path, F_OK) != 0)
	{
		ft_perror("minishell: cd: ", path, ": No such file or directory");
		return (0);
	}
	if (stat(path, &sb) != 0 || !S_ISDIR(sb.st_mode))
	{
		ft_perror("minishell: cd: ", path, ": Not a directory");
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		ft_perror("minishell: cd: ", path, ": Permission denied");
		return (0);
	}
	result = chdir(path);
	if (result != 0)
	{
		ft_perror("minishell: cd: ", path, ": Error");
		return (0);
	}
	return (1);
}
