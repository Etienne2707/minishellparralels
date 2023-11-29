/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:13:06 by educlos           #+#    #+#             */
/*   Updated: 2023/11/29 02:32:56 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_no_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i > 0 && str[i - 1] == ' ')
		i--;
	return (i);
}

int	have_digit(char *str, int i)
{
	while (str[i] != '\0' || str[i] == '|')
	{
		if (str[i] != ' ' && (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A'
				|| str[i] > 'Z') && (str[i] < '0' || str[i] > '9'))
			return (-1);
		i++;
	}
	return (1);
}

int	check_nb_pipe(char *str)
{
	int	i;
	int	c;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			c = 0;
			while (str[i] != '\0' && str[i] == '|')
			{
				i++;
				c++;
			}
			if (c > 1)
				return (-1);
		}
		i++;
	}
	return (1);
}

int	check_start_end(char *str)
{
	int	size;
	int	i;

	size = strlen_no_space(str);
	if (!size)
		return (0);
	i = 0;
	if (str[i] == '|' || str[size - 1] == '|')
		return (-1);
	i++;
	return (0);
}

int	only_special(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '<' && str[i] != '>' && str[i] != '|' && str[i] != ' '
			&& str[i] != 39 && str[i] != 34)
			return (0);
		i++;
	}
	return (-1);
}
