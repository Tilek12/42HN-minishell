/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:32:28 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/30 14:18:58 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	c_leading_quotes(char *token)
{
	int	count;

	count = 0;
	while (token && token[count] && token[count] == '\"')
	{
		count++;
	}
	return (count);
}

static int	c_trailing_quotes(char *token)
{
	int	count;
	int	len;

	count = 0;
	len = ft_strlen(token);
	while (len > 0 && token[len - 1] == '\"')
	{
		count++;
		len--;
	}
	return (count);
}

static int	are_quotes_even(int left_quotes, int right_quotes)
{
	return ((left_quotes % 2 == 0) && (right_quotes % 2 == 0));
}

void	find_quotes(char *token, int *start, int *end)
{
	int	left_quotes;
	int	right_quotes;
	int	len;

	left_quotes = c_leading_quotes(token);
	right_quotes = c_trailing_quotes(token);
	len = ft_strlen(token);
	if (are_quotes_even(left_quotes, right_quotes))
	{
		*start = left_quotes;
		*end = len - right_quotes;
	}
	else
	{
		*start = 0;
		*end = len;
	}
}

char	*c_new_token(char *token, int start, int end)
{
	char	*new_token;
	int		j;

	j = 0;
	new_token = (char *)malloc(end - start + 1);
	if (!new_token)
		return (NULL);
	while (start < end)
		new_token[j++] = token[start++];
	new_token[j] = '\0';
	return (new_token);
}
