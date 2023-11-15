/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:54:15 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 16:59:20 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_double_array(char **to_free)
{
	int	i;

	i = 0;
	while (to_free && to_free[i])
		free(to_free[i++]);
	if (to_free)
		free(to_free);
}

char	**ft_cpy_double_array(char **to_copy)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	while (to_copy && to_copy[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	copy[i] = NULL;
	j = 0;
	while (to_copy && to_copy[j])
	{
		copy[j] = ft_strdup(to_copy[j]);
		if (!copy[j])
			ft_free_double_array(copy);
		j++;
	}
	return (copy);
}

int	var_exists(char **envp, char *str)
{
	int	i;

	i = 0;
	if (str[after_equal(str)] == '\"')
		remove_quotes(str, '\"');
	if (str[after_equal(str)] == '\'')
		remove_quotes(str, '\'');
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, after_equal(envp[i]) - 1) == 0)
		{
			return (1);
		}
		i++;
	}
	printf ("ok");
	return (0);
}

char	**ft_append_double_array(char **matrix, char *to_append)
{
	char	**new_matrix;
	int		i;
	int		j;

	i = 0;
	while (matrix && matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i + 2));
	if (!new_matrix)
		return (NULL);
	new_matrix[i + 1] = NULL;
	j = -1;
	while (++j < i)
	{
		new_matrix[j] = ft_strdup(matrix[j]);
		if (!new_matrix[j])
		{
			ft_free_double_array(new_matrix);
			break ;
		}
	}
	new_matrix[j] = ft_strdup(to_append);
	return (new_matrix);
}

char	**ft_pop_double_array(char **matrix, char *to_pop)
{
	char	**new_matrix;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (matrix && matrix[i])
		i++;
	new_matrix = malloc(sizeof(char *) * (i));
	if (!new_matrix)
		return (NULL);
	new_matrix[i - 1] = NULL;
	j = -1;
	k = 0;
	while (++j < i)
	{
		if (!(ft_strncmp(matrix[j], to_pop, after_equal(matrix[j]) - 1) == 0
				&& matrix[j][ft_strlen(to_pop)] == '='))
		{
			new_matrix[k] = ft_strdup(matrix[j]);
			if (!new_matrix[k])
			{
				ft_free_double_array(new_matrix);
				break ;
			}
			k++;
		}
	}
	return (new_matrix);
}
