/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:18:54 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/27 18:46:17 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*-------------------------------*/
/*  Swap function for quicksort  */
/*-------------------------------*/
void	swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/*------------------------------------*/
/*  Partition function for quicksort  */
/*------------------------------------*/
int	partition(char **arr, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(arr[j], pivot) < 0)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
		j++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

/*----------------------------*/
/*  Quicksort implementation  */
/*----------------------------*/
void	quicksort(char **arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quicksort(arr, low, pi - 1);
		quicksort(arr, pi + 1, high);
	}
}

/*--------------------------------------------------*/
/*  Sort environment variables in alphabetic order  */
/*--------------------------------------------------*/
char	**env_sort(char **env)
{
	char	**sorted_env;
	int		len_env;
	int		index;

	sorted_env = env_set(env);
	if (!sorted_env)
		return (NULL);
	index = env_var_find(sorted_env, "_");
	if (index != -1)
	{
		if (env_var_remove(&sorted_env, index) < 0)
			return (NULL);
	}
	len_env = env_len(sorted_env);
	quicksort(sorted_env, 0, len_env - 1);
	return (sorted_env);
}
