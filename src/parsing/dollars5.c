/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 02:25:06 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/30 08:39:05 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_last_word(char *str, int i)
{
	while (str[i] == 32 && str[i] != 0)
	{
		i++;
	}
	if (str[i] == 0)
		return (1);
	else
		return (0);
}

int	ft_strlen_wspace(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != 0 && str[i] == 32)
		i++;
	while (i < ft_strlen(str) && str[i] != '\0')
	{
		if (str[i] == 32)
		{
			while (str[i] == 32 && str[i] != '\0')
				i++;
			len++;
		}
		i++;
		len++;
	}
	return (len);
}

char	*remove_space(char *str)
{
	int		i;
	int		len;
	char	*new;

	new = malloc(sizeof(char) * ft_strlen_wspace(str) + 1);
	if (!new)
		return (NULL);
	len = 0;
	i = 0;
	while (str[i] != 0 && str[i] == 32)
		i++;
	while (i < ft_strlen(str) && str[i] != '\0')
	{
		if (str[i] != 32 || (str[i] == 32 && !is_last_word(str, i)))
			new[len++] = str[i];
		if (str[i++] == 32)
			while (str[i] == 32 && str[i] != '\0')
				i++;
	}
	new[len] = '\0';
	free(str);
	return (new);
}
