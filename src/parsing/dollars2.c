/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:18:00 by educlos           #+#    #+#             */
/*   Updated: 2023/11/27 07:11:38 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_dquote(char *str)
{
	int		i;
	int		k;
	char	*new;

	k = 0;
	i = 0;
	new = malloc(sizeof(char) * ft_strlen(str) + 3);
	if (!new)
		return (NULL);
	new[k++] = 34;
	while (str[i] != '\0')
	{
		new[k++] = str[i++];
	}
	new[k++] = 34;
	new[k] = '\0';
	free(str);
	return (new);
}

char	*strcpyn(char *dest, char *src, int index, int size)
{
	int	i;

	i = 0;
	while (size > 1 && src[index] != '\0')
	{
		dest[i] = src[index];
		index++;
		i++;
		size--;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_in_quote2(char *str, int index)
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
				return (0);
		}
		else if (str[i] == 39)
		{
			start = ++i;
			while ((str[i] != 39) && str[i] != '\0')
				i++;
			if (index >= start && index < i)
				return (0);
		}
		i++;
	}
	return (1);
}

char	*change_value2(char *new, char *str, int size, int index)
{
	while (str[size] != '\0')
	{
		new[index] = str[size];
		size++;
		index++;
	}
	new[index] = '\0';
	return (new);
}

char	*change_value(char *env, char *str)
{
	int		size;
	char	*new;
	int		i;
	int		index;

	i = 0;
	index = get_index(str);
	env = add_quote(env,str);
	size = index + 1;
	while (str[size] != '\0' && str[size] != 32 && str[size] != '$'
		&& str[size] != 39 && str[size] != 34 && is_n_a(str[size]) == 1)
		if (str[size++] == '?')
			break ;
	new = malloc(sizeof(char *) * (ft_strlen(str) - (size - index))
			+ ft_strlen(env) + 1 + 2);
	if (!new)
		return (NULL);
	new = ft_strncpy(new, str, index);
	while (env[i] != '\0')
		new[index++] = env[i++];
	new = change_value2(new, str, size, index);
	free(env);
	free(str);
	return (new);
}
