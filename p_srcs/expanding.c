/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/14 22:07:58 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	not_in_squote(char *token, int i)
{
	int	x;
	int	left;
	int	right;

	x = i;
	left = 0;
	right = 0;
	while (i >= 0)
	{
		if (token[i] == '\'')
			left = 1;
		i--;
	}
	while (token[x])
	{
		if (token[x] == '\'')
			right = 1;
		x++;
	}
	if (right && left)
		return (0);
	return (1);
}

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
	int	check;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	check = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (token[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		if (token[i] == '$' && !in_single_quote)
			check++;
		i++;
	}
	return (check > 0);
}

// int	still_dollar_sign_there(char *token)
// {
// 	int	i;
// 	int	check;

// 	i = 0;
// 	check = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '$')
// 			check = check + not_in_squote(token, i);
// 		i++;
// 	}
// 	if (check > 0)
// 		return (1);
// 	else
// 		return (0);
// }

int	expansion_of_first_token(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !count_str(token[i]) && not_in_squote(token, i))
			break ;
		i++;
	}
	printf("the i = %d\n",i);
	return (i);
}

char	*remove_double_quotes(char *str)
{
	int	len;

	int i, j = 0;
	len = strlen(str);
	char *result = malloc(len + 1); // Allocate memory for the result string
	if (!result)
		return (NULL); // Handle memory allocation failure
	for (i = 0; i < len; i++)
	{
		if (str[i] != '"')
		{ // Skip double quotes
			result[j] = str[i];
			j++;
		}
	}
	result[j] = '\0'; // Null-terminate the result string
	return (result);
}
/*
	this function is responsible for expanding a certain token with ($) within the array
*/

void	expand(char **tokens, char **env, t_data *data)
{
	int		i;
	int		x;
	char	*expanded_token;
	char	*dollar_ptr;

	i = 0;
	while (tokens[i])
	{
		if (expansion_of_first_token(tokens[i]) != -1)
		{
			dollar_ptr = ft_strchr(tokens[i], '$');
			printf("here3\n");
			// printf(" !dollar_ptr = %d || dollar_ptr[1] == \'\\0\' = %d || count_str(dollar_ptr[1] = %d) \
			// 	|| is_exeption(dollar_ptr[1]) = %d\n", !dollar_ptr , dollar_ptr[1] == '\0', count_str(dollar_ptr[1])
			// 	, is_exeption(dollar_ptr[1]));
			printf(" !dollar_ptr = %d\n", !dollar_ptr);
			if (!dollar_ptr || dollar_ptr[1] == '\0' || count_str(dollar_ptr[1])
				|| is_exeption(dollar_ptr[1]))
			{
				i++;
				printf("here1\n");
				continue ;
			}
			x = expansion_of_first_token(tokens[i]);
			expanded_token = dollar_sign(tokens[i], tokens[i] + x + 1, env,
					data);
			free(tokens[i]);
			tokens[i] = remove_double_quotes(expanded_token);
			free(expanded_token);
		}
		printf("here2\n");
		if (still_dollar_sign_there(tokens[i]))
			continue ;
		//we need to adoiv to go to the next token if I have more than one $
		i++;
	}
}

// echo HOME$USER$USER"HOME    "
// void	expand(char **tokens, char **env, t_data *data)
// {
// 	int		i;
// 	int		x;
// 	char	*expanded_token;
// 	char	*dollar_ptr;

// 	i = 0;
// 	while (tokens[i])
// 	{
// 		if (expansion_of_first_token(tokens[i]) != -1)
// 		// Check if the current token needs expansion
// 		{
// 			dollar_ptr = ft_strchr(tokens[i], '$');
// 			if (!dollar_ptr || dollar_ptr[1] == '\0' || count_str(dollar_ptr[1])
// 				|| is_exeption(dollar_ptr[1]))
// 			// If no $ found or $ is at the end or a special case, skip
// 			{
// 				i++;
// 				continue ;
// 			}
// 			x = expansion_of_first_token(tokens[i]);
// 			// Getting the length of the expansion target
// 			expanded_token = dollar_sign(tokens[i], tokens[i] + x + 1, env,
// 					data);
// 			// Expand the token based on the environment variables
// 			tokens[i] = expanded_token;
// 		}
// 		if (still_dollar_sign_there(tokens[i]))
// 			continue ;
// 		i++;
// 	}
// }

// int main() {
// 	t_ryusupov env_struct = {
// 		.PATH = "/usr/bin:/bin",
// 		.HOME = "/home/user",
// 		.VAR = "value"
// 	};
// 	t_ryusupov* env = &env_struct;

// 	char* tokens[] = {
// 		"echo $PATH",
// 		"ls -l $HOME",
// 		"echo 'This $VAR should not expand'",
// 		"echo \"This $VAR should expand\"",
// 		NULL
// 	};

// 	expand(tokens, &env);

// 	for (int i = 0; tokens[i] != NULL; i++) {
// 		printf("Token %d: %s\n", i, tokens[i]);
// 	}

// 	for (int i = 0; tokens[i] != NULL; i++) {
// 		free(tokens[i]);
// 	}

// 	return (0);
// }

// int main() {
//     // Mock environment variable. Replace with actual environment setup.
//     t_ryusupov* env = NULL;
// Assuming t_ryusupov is a structure for environment variables.

//     // Example tokens array to be expanded.
//     char* tokens[] = {
//         "echo $PATH",
//         "ls -l $HOME",
//         "echo 'This $VAR should not expand'",
//         "echo \"This $VAR should expand\"",
//         NULL // Array terminator
//     };

//     // Call the expand function.
//     expand(tokens, &env);

//     // Print the expanded tokens.
//     for (int i = 0; tokens[i] != NULL; i++) {
//         printf("Token %d: %s\n", i, tokens[i]);
//     }

//     // Free the allocated memory for tokens.
//
// Note: This is necessary because the expand function replaces tokens with dynamically allocated strings.
//     for (int i = 0; tokens[i] != NULL; i++) {
//         free(tokens[i]);
//     }

//     return (0);
// }
