/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:18:07 by educlos           #+#    #+#             */
/*   Updated: 2023/10/25 18:38:33 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *env, char *str)
{
	int		i;
	int		c;
	char	*value;

	i = ft_strlen(str) + 1;
	c = 0;
	if (ft_compare(str, env, ft_strlen(str)) != 0)
		return (NULL);
	value = malloc(sizeof(char) * ft_strlen(env) - ft_strlen(str) + 1);
	if (!value)
		return (NULL);
	while (env[i] != '\0')
	{
		value[c] = env[i];
		i++;
		c++;
	}
	value[c] = '\0';
	printf("%s\n", value);
	free(str);
	return (value);
}

char	*remove_dol(char *str, char *value)
{
	int		i;
	char	*new;
	int		c;

	i = 0;
	c = 0;
	new = malloc(sizeof(char) * ft_strlen(str) - ft_strlen(value) + 1);
	if (!new)
		return (NULL);
	while (str[i] != '$' && dollars_in_quote(str, i) == 1 && str[i] != '\0')
	{
		new[c++] = str[i++];
	}
	i = i + ft_strlen(value) + 1;
	while (str[i] != '\0')
	{
		new[c++] = str[i++];
	}
	new[c] = '\0';
	free(value);
	return (new);
}

char	*swap_value(char *value, char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	while (envp[i] != NULL)
	{
		temp = get_env(envp[i], value);
		if (temp != NULL)
			return (temp);
		i++;
	}
	free(temp);
	return (NULL);
}

char	*get_value(char *str, int index)
{
	int		i;
	char	*value;

	i = index + 1;
	while (str[i] != '\0' && str[i] != 32 && str[i] != '$' && str[i] != 39
		&& str[i] != ']' && str[i] != 34)
		i++;
	value = malloc(sizeof(char) * (i - index) + 1);
	if (!value)
		return (NULL);
	value = strcpyn(value, str, index + 1, i - index);
	return (value);
}

char	*ft_dollars(char *str, char **envp, char *dest)
{
	int		i;
	char	*temp;

	i = 0;
	dest = str;
	while (str[i] != 0)
	{
		if (str[i] == '$' && dollars_in_quote(str, i) == 1)
		{
			temp = swap_value(get_value(str, i), envp);
			if (temp != NULL)
				dest = change_value(temp, dest);
			else
				dest = remove_dol(dest, get_value(str, i));
		}
		i++;
	}
	return (dest);
}
