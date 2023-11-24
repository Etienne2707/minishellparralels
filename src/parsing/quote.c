/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:39 by educlos           #+#    #+#             */
/*   Updated: 2023/10/25 18:38:48 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_woquotes(char *str, char *dest)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 && check_in_quote(str, i) == -1)
			i++;
		else if (str[i] == 39 && check_in_quote(str, i) == -1)
			i++;
		else
			dest[k++] = str[i++];
	}
	dest[k] = '\0';
	return (dest);
}

int	only_quotes(char *str)
{
	int i;
	int result;
	
	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 34 && str[i] != 39)
			result = 1;
		i++;
	}
	return (result);
}

char	*ft_remove_quote(char *str)
{
	int		k;
	int		c;
	char	*dest;

	k = 0;
	c = 0;
	if (only_quotes(str) == 0)
	{
		// faire tous ca dans une fonction differentes
		free(str)
		dest = malloc(sizeof(char ) * 2);
		dest[0] = 32;
		dest[1] = '\0';
		return (dest);
	}
	while (str[k] != '\0')
	{
		if ((str[k] == 34 || str[k] == 39) && check_in_quote(str, k) == -1)
			c++;
		k++;
	}
	if (c == 0 || c == 1)
		return (str);
	dest = malloc(sizeof(char) * ft_strlen(str) - c + 1);
	if (!dest)
		return (NULL);
	dest = string_woquotes(str, dest);
	free(str);
	return (dest);
}

int	check_in_quote(char *str, int index)
{
	int	i;
	int	start;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			start = ++i;
			while ((str[i] != 34) && str[i] != '\0')
				i++;
			if (index >= start && index < i)
				return (1);
		}
		else if (str[i] == 39)
		{
			start = ++i;
			while ((str[i] != 39) && str[i] != '\0')
				i++;
			if (index >= start && index < i)
				return (1);
		}
		i++;
	}
	return (-1);
}
