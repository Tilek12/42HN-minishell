/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:27:31 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/18 19:37:08 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function checks if the begining of the given arguments is not this tokens if it is the function returns an error
*/
int	check_beginning_and_end(char **t, int i)
{
	if (ft_strncmp(t[i], ">", 1) == 0 || ft_strncmp(t[i], "<", 1) == 0)
		return (0);
	else if (t[i] && (ft_strncmp(t[0], "|", 1) == 0 || (i >= 1
					&& ft_strncmp(t[i], "|", 1) == 0)))
		return (0);
	return (1);
}
/*
	here im cheching for the tokens if the are correctly given
	e.g: cat < | wc -l OR echo helloWorld > > log.txt
*/
int	parse_redirs(char *current, char *next)
{
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "\n", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "\n", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	return (0);
}
/*
	This function counts number of single or double quotes
	if number of any of them is odd that means that quote is not closed
*/

// int quotes_check(char *t)
// {
//     int i;
//     int squote;
//     int dquote;

//     i = 0;
//     squote = 0;
//     dquote = 0;
//     while (t[i])
//     {
//         if (t[i] == '\'')
//             squote++;
//         if (t[i] == '\"')
//             dquote++;
//         i++;
//     }
//     if (squote % 2 != 0 || dquote % 2 != 0)
//         return (-1);
//     return (0);
// }

int	quotes_check(char *t)
{
	int	i;
	int	squote;
	int	dquote;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	squote = 0;
	dquote = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (t[i])
	{
		if (t[i] == '\'' && !in_double_quote)
		{
			if (in_single_quote)
				in_single_quote = 0;
			else
				in_single_quote = 1;
			squote++;
		}
		if (t[i] == '\"' && !in_single_quote)
		{
			if (in_double_quote)
				in_double_quote = 0;
			else
				in_double_quote = 1;
			dquote++;
		}
		i++;
	}
	if (squote % 2 != 0 || dquote % 2 != 0)
		return (-1);
	return (0);
}

int	parse(char **t, t_data *data)
{
	int	i;

	i = 0;
	if (t[i] == NULL)
		return (1);
	while (t[i])
	{
        // printf("%s\n", t[i]);
		if (quotes_check(t[i]) < 0)
		{
			ft_perror_parsing("minishell: ", "syntax error near unexpected token ", t[i], data->exit_code);
			return (1);
		}
		if (t[i + 1] && (((strncmp(t[i], "|", 1) == 0) && (strncmp(t[i + 1],
							"|", 1) == 0)) || parse_redirs(t[i], t[i + 1]) < 0))
		{
			ft_perror_parsing("minishell: ", "syntax error near unexpected token ", t[i], data->exit_code);
			return (1);
		}
		i++;
	}
	if (!check_beginning_and_end(t, i - 1))
    {
        ft_perror_parsing("minishell: ", "syntax error near unexpected token `newline'", t[i], data->exit_code);
		return (1);
    }
	return (0);
}

// int main() {
//     char *test0[] = {"echo", "hello", "world", NULL};
//     char *test1[] = {"echo", "\"hello world\"", ">", "output.txt", NULL};
//     char *test2[] = {"cat", "<", "input.txt", "|", "grep", "search_term",
	// NULL};
//     char *test3[] = {"ls", "<", NULL};
//     char *test4[] = {"|", "echo", "error", NULL}; // Invalid test case
//     char *test5[] = {"echo", "unmatched", "\"", NULL}; // Invalid test case
//     char *test6[] = {"echo", "multiple", ">", ">", "error", NULL};
	// Invalid test case

// 	if (parse(test0) == 0)
// 		printf("Test 0 passed.\n");
// 	else
// 		printf("test 0 failed,\n");
//     if (parse(test1) == 0)
//         printf("Test 1 passed.\n");
//     else
//         printf("Test 1 failed.\n");

//     if (parse(test2) == 0)
//         printf("Test 2 passed.\n");
//     else
//         printf("Test 2 failed.\n");

//     if (parse(test3) == 0)
//         printf("Test 3 passed.\n");
//     else
//         printf("Test 3 failed.\n");

//     if (parse(test4) != 0)
//         printf("Test 4 passed.\n");
//     else
//         printf("Test 4 failed.\n");

//     if (parse(test5) != 0)
//         printf("Test 5 passed.\n");
//     else
//         printf("Test 5 failed.\n");

//     if (parse(test6) != 0)
//         printf("Test 6 passed.\n");
//     else
//         printf("Test 6 failed.\n");

//     return (0);
// }
