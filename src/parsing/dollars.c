/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:18:07 by educlos           #+#    #+#             */
/*   Updated: 2023/11/30 09:13:47 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
	while (is_solo_dol(str, i) == 0 && dollars_in_quote(str, i) == 1
		&& d_hd(str, i) != -1 && str[i] != '\0')
	{
		new[c++] = str[i++];
	}
	i = i + ft_strlen(value) + 1;
	while (str[i] != '\0')
	{
		new[c++] = str[i++];
	}
	new[c] = '\0';
	free(str);
	free(value);
	return (new);
}

char	*swap_value(char *value, char **envp)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_strcmp(value, "?") == 0)
	{
		free(value);
		if (g_exit_status == -1)
			return (temp = ft_itoa(130));
		if (g_exit_status == -2)
			return (temp = ft_itoa(0));
		return (temp = ft_itoa(g_exit_status));
	}
	while (envp[i] != NULL)
	{
		temp = get_env(envp[i], value);
		if (temp != NULL)
			return (temp);
		i++;
	}
	if (value != NULL)
		free(value);
	free(temp);
	return (NULL);
}

char	*get_exp_num(char *str, int index)
{
	char	*dest;

	dest = malloc(sizeof(char ) * 2);
	if (!dest)
		return (NULL);
	dest[0] = str[index + 1];
	dest[1] = '\0';
	return (dest);
}

char	*get_value(char *str, int index)
{
	int		i;
	char	*value;

	i = index + 1;
	if (is_solo_dol(str, index) == -1)
		return (get_exp_num(str, index));
	while (str[i] != '\0' && str[i] != 32 && str[i] != '$' && str[i] != 39
		&& str[i] != 34 && is_n_a(str[i]) == 1)
	{
		if (str[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	value = malloc(sizeof(char) * (i - index) + 1);
	if (!value)
		return (NULL);
	value = strcpyn(value, str, index + 1, i - index);
	return (value);
}

char	*ft_dollars(char *str, char **envp, char *dest)
{
	if (!dest)
		return (NULL);
	dest = ft_dollars2(str, envp, dest);
	return (dest);
}
