/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/30 14:35:51 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remove_double_quotes(char *token)
{
	int		start;
	int		end;
	char	*new_token;

	find_quotes(token, &start, &end);
	new_token = c_new_token(token, start, end);
	free(token);
	return (new_token);
}

static char	*remove_single_quotes(char *token)
{
	int		start;
	int		end;
	char	*new_token;

	count_and_find_quotes(token, &start, &end);
	new_token = create_new_token(token, start, end);
	free(token);
	return (new_token);
}

static int	expansion_of_first_token(char *token)
{
	int	i;

	i = 0;
	while (token && token[i])
	{
		if (token[i] == '$' && !count_str(token[i]) && not_in_squote(token, i))
		{
			if (token[i + 1] == '\0' || token[i + 1] == '$' || token[i
					+ 1] == ' ' || is_exeption(token[i + 1]))
				return (-1);
			break ;
		}
		i++;
	}
	return (i);
}

static void	get_env_var(char **token, char **env, t_data *data)
{
	int		x;
	char	*expanded_token;
	char	*dollar_ptr;

	if (token == NULL || *token == NULL)
		return ;
	dollar_ptr = ft_strchr(*token, '$');
	if (!dollar_ptr || dollar_ptr[1] == '\0' || dollar_ptr[1] == ' ')
		return ;
	if (dollar_ptr[1] == '"' || dollar_ptr[1] == '\'')
		ft_memmove(dollar_ptr, dollar_ptr + 1, ft_strlen(dollar_ptr));
	x = expansion_of_first_token(*token);
	if (x == -1)
		return ;
	expanded_token = dollar_sign(*token, *token + x + 1, env, data);
	free(*token);
	*token = expanded_token;
}

/*
	this function is responsible for expanding a certain token
	with ($) within the array
*/
void	expand(char **tokens, char **env, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i] && j < MAX)
	{
		tokens[i] = remove_double_quotes(tokens[i]);
		tokens[i] = remove_single_quotes(tokens[i]);
		get_env_var(&tokens[i], env, data);
		if (still_dollar_sign_there(tokens[i]) && tokens[i][0] != '\0')
		{
			if (expansion_of_first_token(tokens[i]) == -1)
				break ;
			j++;
			continue ;
		}
		i++;
	}
}
