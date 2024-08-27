/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:29:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:23:45 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*------------------------------------*/
/*  Check if the argument is heredoc  */
/*------------------------------------*/
int	is_heredoc(char *arg)
{
	if (ft_strncmp(arg, "<<", 2) == 0
		&& ft_strlen(arg) == 2)
		return (1);
	else
		return (0);
}

/*----------------------------------------------*/
/*  Check if the argument is input redirection  */
/*----------------------------------------------*/
int	is_redir_input(char *arg)
{
	if (ft_strncmp(arg, "<", 1) == 0
		&& ft_strlen(arg) == 1)
		return (1);
	else
		return (0);
}

/*-----------------------------------------------*/
/*  Check if the argument is output redirection  */
/*-----------------------------------------------*/
int	is_redir_otput(char *arg)
{
	if (ft_strncmp(arg, ">", 1) == 0
		&& ft_strlen(arg) == 1)
		return (1);
	else
		return (0);
}

/*------------------------------------------------------*/
/*  Check if the argument is output append redirection  */
/*------------------------------------------------------*/
int	is_redir_append(char *arg)
{
	if (ft_strncmp(arg, ">>", 2) == 0
		&& ft_strlen(arg) == 2)
		return (1);
	else
		return (0);
}

/*----------------------------------------*/
/*  Check if the argument is redirection  */
/*----------------------------------------*/
int	is_redirection(char *arg)
{
	if (is_heredoc(arg)
		|| is_redir_input(arg)
		|| is_redir_otput(arg)
		|| is_redir_append(arg))
		return (1);
	else
		return (0);
}
