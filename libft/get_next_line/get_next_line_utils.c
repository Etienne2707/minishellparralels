/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:49:22 by mle-duc           #+#    #+#             */
/*   Updated: 2023/04/11 06:25:50 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	reset(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_realloc(char *str, char *to_cat)
{
	char	*ret;
	int		i;
	int		j;

	if (!str && !to_cat)
		return (0);
	ret = malloc(sizeof(char) * (ft_strlen(str) + ft_strlen(to_cat) + 1));
	if (!ret)
	{
		free(str);
		return (0);
	}
	i = 0;
	j = 0;
	while (str && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	while (to_cat && to_cat[j])
		ret[i++] = to_cat[j++];
	ret[i] = 0;
	free(str);
	return (ret);
}

/*
int	ft_strlen(char *str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count])
		count++;
	return (count);
}
*/

int	find_nl(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
char	*ft_strdup(char *str)
{
	int		i;
	char	*dup;

	if (!str)
		return (0);
	dup = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dup)
		return (0);
	i = 0;
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}*/
