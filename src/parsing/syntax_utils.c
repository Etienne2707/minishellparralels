/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:11:50 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 12:24:17 by mle-duc          ###   ########.fr       */
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
