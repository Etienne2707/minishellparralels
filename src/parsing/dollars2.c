/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:18:00 by educlos           #+#    #+#             */
/*   Updated: 2023/11/16 12:02:37 by mle-duc          ###   ########.fr       */
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
	size = index + 1;
	while (str[size] != '\0' && str[size] != 32 && str[size] != '$'
		&& str[size] != 39 && str[size] != 34)
		size++;
	new = malloc(sizeof(char *) * (ft_strlen(str) - (size - index))
			+ ft_strlen(env) + 1);
	if (!new)
		return (NULL);
	new = ft_strncpy(new, str, index);
	while (env[i] != '\0')
		new[index++] = env[i++];
	new = change_value2(new, str, size, index);
	free(env);
	return (new);
}
