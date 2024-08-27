/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:18:32 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 20:31:24 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*---------------------------------------------*/
/*  Find node by index in command linked list  */
/*---------------------------------------------*/
t_cmd	*cmd_list_find(t_cmd *head, int index)
{
	t_cmd	*current;

	if (head == NULL || index < 0)
		return (NULL);
	current = head;
	while (current)
	{
		if (current->index == index)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*-----------------------------------------*/
/*  Find last node in command linked list  */
/*-----------------------------------------*/
t_cmd	*cmd_list_last(t_cmd *head)
{
	t_cmd	*last;

	if (head == NULL)
		return (NULL);
	last = head;
	while (last->next != NULL)
	{
		last = last->next;
	}
	return (last);
}

/*---------------------------------------*/
/*  Add new node to command linked list  */
/*---------------------------------------*/
void	cmd_list_add(t_cmd *head, t_cmd *new)
{
	t_cmd	*current;

	if (head == NULL || new == NULL)
		return ;
	else
	{
		current = cmd_list_last(head);
		new->index = current->index + 1;
		current->next = new;
	}
}

/*---------------------------------*/
/*  Length of command linked list  */
/*---------------------------------*/
int	cmd_list_len(t_cmd *head)
{
	int		length;
	t_cmd	*current;

	length = 0;
	current = head;
	while (current->next != NULL)
	{
		length++;
		current = current->next;
	}
	return (length);
}
