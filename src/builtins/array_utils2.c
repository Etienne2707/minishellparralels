/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:35:07 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/30 01:38:22 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_pop_2(char **matrix, char ***new_matrix, int i, char *to_pop)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	while (++j < i)
	{
		if (!(ft_strncmp(matrix[j], to_pop, after_equal(matrix[j]) - 1) == 0
				&& (ft_strlen(to_pop) < after_equal(matrix[j])
				&& matrix[j][ft_strlen(to_pop)] == '=')))
		{
			(*new_matrix)[k] = ft_strdup(matrix[j]);
			if (!(*new_matrix)[k])
			{
				ft_free_double_array((*new_matrix));
				break ;
			}
			k++;
		}
	}
}

char	**ft_pop_double_array(char **matrix, char *to_pop)
{
	char	**new_matrix;
	int		i;

	i = 0;
	while (matrix && matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i));
	if (!new_matrix)
		return (NULL);
	new_matrix[i - 1] = NULL;
	ft_pop_2(matrix, &new_matrix, i, to_pop);
	return (new_matrix);
}
