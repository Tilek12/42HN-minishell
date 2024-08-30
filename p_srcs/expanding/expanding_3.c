/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:17:20 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/30 14:36:33 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_exeption(char c)
{
	if (c == '/' || c == '=' || c == '\"' || c == '$' || c == '\\')
		return (1);
	if (c == '\'' || c == '+' || c == '-')
		return (1);
	return (0);
}

int	still_dollar_sign_there(char *token)
{
	int	i;
	int	in_single_quote;
	int	check;

	i = 0;
	check = 0;
	in_single_quote = 0;
	while (token && token[i])
	{
		if (token[i] == '\'')
		{
			in_single_quote = !in_single_quote;
			i++;
			continue ;
		}
		if (token[i] == '$' && !in_single_quote && token[i + 1] != '\0')
		{
			check++;
		}
		i++;
	}
	return (check > 0);
}

int	calculate_new_length(const char *var, const char *exit_code_str)
{
	int	i;
	int	new_length;

	i = 0;
	new_length = 0;
	while (var[i])
	{
		if (var[i] == '?')
			new_length += ft_strlen(exit_code_str);
		else
			new_length++;
		i++;
	}
	return (new_length);
}

void	build_result_string(const char *var, char *result,
		const char *exit_code_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '?')
		{
			strcpy(&result[j], exit_code_str);
			j += ft_strlen(exit_code_str);
		}
		else
		{
			result[j] = var[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
}

char	*replace_question(const char *var, int *exit_code)
{
	char	*exit_code_str;
	int		new_length;
	char	*result;

	exit_code_str = ft_itoa(*exit_code);
	if (!exit_code_str)
		return (NULL);
	new_length = calculate_new_length(var, exit_code_str);
	result = (char *)malloc((new_length + 1) * sizeof(char));
	if (!result)
	{
		free(exit_code_str);
		return (NULL);
	}
	build_result_string(var, result, exit_code_str);
	free(exit_code_str);
	return (result);
}
