/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 02:25:06 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/30 02:25:42 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_wspace(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 32)
		{
			while (str[i] == 32 && str[i] != '\0')
				i++;
			len++;
		}
		if (i >= ft_strlen(str))
			break ;
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
	while (str[i] != '\0')
	{
		if (str[i] == 32)
		{
			new[len++] = str[i++];
			while (str[i] == 32 && str[i] != '\0')
				i++;
		}
		if (i >= ft_strlen(str))
			break ;
		new[len++] = str[i++];
	}
	new[len] = '\0';
	free(str);
	return (new);
}
