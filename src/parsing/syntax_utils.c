/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:11:50 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/28 18:26:25 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	syntax1(char *str, int *s, int *i)
{
	*i = *i + 1;
	while (str[*i] != 34 && str[*i] != 0)
	{
		if (str[*i] == 39)
			*s = *s - 1;
		*i = *i + 1;
	}
}

static void	syntax2(char *str, int *d, int *i)
{
	*i = *i + 1;
	while (str[*i] != 39 && str[*i] != 0)
	{
		if (str[*i] == 34)
			*d = *d - 1;
		*i = *i + 1;
	}
}

void	syntax_quote2(char *str, int *s, int *d, int *i)
{
	if (str[*i] == 34)
		syntax1(str, s, i);
	else if (str[*i] == 39)
		syntax2(str, d, i);
}

static void	index_in_quotes(char *dest, char c, int *i)
{
	(*i)++;
	while (dest[*i] != c && dest[*i] != 0)
		(*i)++;
	(*i)++;
}

void	replace_whitespaces(char *dest)
{
	int	i;

	if (!dest)
		return ;
	i = 0;
	while (dest[i])
	{
		while (dest[i] == 34 || dest[i] == 39)
		{
			if (dest[i] == 34)
				index_in_quotes(dest, 34, &i);
			else if (dest[i] == 39)
				index_in_quotes(dest, 39, &i);
		}
		if (dest[i] == 0)
			return ;
		if (dest[i] >= 9 && dest[i] <= 13)
			dest[i] = 32;
		i++;
	}
}
