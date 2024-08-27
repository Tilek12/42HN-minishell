/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:03:23 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:38:16 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_words_num(const char *s, char c)
{
	int	word_counter;
	int	in_word;

	word_counter = 0;
	in_word = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (in_word)
				in_word = 0;
		}
		else
		{
			if (!in_word)
			{
				in_word = 1;
				word_counter++;
			}
		}
		s++;
	}
	return (word_counter);
}

static char	*next_word(const char **s, char c)
{
	const char	*p_start;
	char		*word;
	size_t		len;

	p_start = *s;
	len = 0;
	while (**s && (**s == c))
		(*s)++;
	while (((*s)[len]) && ((*s)[len] != c))
		len++;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, p_start, len);
	word[len] = '\0';
	*s += len;
	return (word);
}

static void	free_str(char **str, int i)
{
	while (i--)
		free(str[i]);
	free(str);
}

static int	calc(char **str, const char **s, char c, int *i)
{
	str[*i] = next_word(s, c);
	if (!str[*i])
	{
		free_str(str, *i);
		return (0);
	}
	(*i)++;
	return (1);
}

/*-----------------------------------------------*/
/*  Split words from string and create 2D array  */
/*-----------------------------------------------*/
char	**split_str(char const *s, char c)
{
	char	**str;
	int		words_num;
	int		i;

	if (!s)
		return (NULL);
	words_num = count_words_num(s, c);
	str = (char **)malloc((words_num + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!calc(str, &s, c, &i))
				return (NULL);
		}
		else
			s++;
	}
	str[words_num] = NULL;
	return (str);
}
