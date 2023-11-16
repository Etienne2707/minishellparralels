/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:13:06 by educlos           #+#    #+#             */
/*   Updated: 2023/11/16 15:26:09 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlen_no_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (str[i - 1] == ' ')
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

int	check_start_end(char *str)
{
	int	size;
	int	i;

	size = strlen_no_space(str);
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

char	*malloc_cpy(char *dest, char *src)
{
	if (!src || src[0] == 0)
		return (NULL);
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	dest = ft_strcpy(dest, src);
	dest[ft_strlen(src)] = '\0';
	return (dest);
}
