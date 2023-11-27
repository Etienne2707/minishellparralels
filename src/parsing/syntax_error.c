/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:00 by educlos           #+#    #+#             */
/*   Updated: 2023/11/25 12:56:20 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wserror(void)
{
	write(2, "Syntax Error", 12);
}

int	check_red_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			while (str[i] == '>' || (str[i] == '<' && str[i] != '\0'))
				i++;
			while (str[i] == 32 && str[i] != '\0')
				i++;
			if (str[i] == '>' || (str[i] == '<' || str[i] == '\0'))
				return (-1);
		}
		i++;
	}
	return (1);
}

int	check_in_out(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '>' && str[i + 1] == '<' && str[i + 1] != '\0')
			return (-1);
		else if (str[i] == '<' && str[i + 1] == '>' && str[i + 1] != '\0')
			return (-1);
		i++;
	}
	return (1);
}

int	syntax_red(char *str)
{
	int		i;
	char	c;
	int		k;

	i = 0;
	while (i < ft_strlen(str) && str[i] != '\0')
	{
		k = 0;
		if ((str[i] == '>' && check_in_quote(str, i) == -1) || (str[i] == '<'
				&& check_in_quote(str, i) == -1))
		{
			c = str[i];
			while (c == str[i] && str[i] != '\0')
			{
				i++;
				k++;
			}
			if (k > 2)
				return (-1);
		}
		i++;
	}
	if (check_in_out(str) == -1 || check_red_arg(str) == -1)
		return (-1);
	return (1);
}

int	syntax_charac(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ';' && check_in_quote(str,i) != 1) && (str[i] == '\'' && check_in_quote(str,i) != 1) )
		{
			return (-1);
		}
		i++;
	}
	return (0);
}
