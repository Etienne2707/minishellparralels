/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:06:59 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 12:23:21 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nb_d_quotes(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34)
			c++;
		i++;
	}
	return (c);
}

static int	nb_s_quotes(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 39)
			c++;
		i++;
	}
	return (c);
}

static int	syntax_quote(char *str)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	d = nb_d_quotes(str);
	s = nb_s_quotes(str);
	while (str[i] != '\0')
	{
		syntax_quote2(str, &s, &d, &i);
		i++;
	}
	if ((d % 2 != 0) || (s % 2 != 0))
		return (0);
	return (1);
}

int	syntax_check(char *str)
{
	if (syntax_quote(str) == 0)
		return (0);
	return (1);
}

int	check_pipe(char **cmd, char *str)
{
	int	i;
	int	k;
	int	c;

	i = 0;
	c = 0;
	if (check_start_end(str) == -1)
		return (-1);
	while (cmd[i] != 0)
	{
		k = 0;
		c = 0;
		while (cmd[i][k] != '\0')
		{
			if (cmd[i][k] != ' ')
				c++;
			k++;
		}
		if (c == 0)
			return (-1);
		i++;
	}
	return (1);
}
