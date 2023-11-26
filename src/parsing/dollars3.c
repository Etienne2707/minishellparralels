/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:57:19 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 12:02:22 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_solo_dol(char *str, int index)
{
	int	i;

	i = index + 1;
	if (str[index] != '$')
		return (0);
	if (dollars_in_quote(str, index) == -1)
		return (0);
	if (str[i] == 32 || str[i] == '\0')
		return (0);
	if ((str[i] >= '0' && str[i] <= '9'))
		return (-1);
	if ((str[i] == 34 || str[i] == 39) && check_in_quote(str, index) == 1)
		return (0);
	return (1);
}

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
	free(str);
	return (value);
}

int	dollars_in_quote(char *str, int index)
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
				return (-1);
		}
		i++;
	}
	return (1);
}

int	get_index(char *str)
{
	int	i;

	i = 0;
	while (!(is_solo_dol(str, i) == 1 && d_hd(str,i) == 1))
	{
		i++;
	}
	return (i);
}
