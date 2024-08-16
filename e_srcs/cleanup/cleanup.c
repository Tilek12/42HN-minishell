/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:25:00 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 12:26:43 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_tokens(t_data *data)
{
	free_array(data->tokens);
	data->tokens = NULL;
	free_list(&data->cmd_list);
	data->cmd_list = NULL;
}
