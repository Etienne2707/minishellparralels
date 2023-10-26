/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:00 by educlos           #+#    #+#             */
/*   Updated: 2023/10/26 15:39:05 by mle-duc          ###   ########.fr       */
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
	while (str[i] != '\0')
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
		if ((str[i] != ' ' && str[i] != '$' && str[i] != '.' && str[i] != '='
				&& str[i] != '|' && str[i] != '>' && str[i] != 39
				&& str[i] != 34 && str[i] != '-' && str[i] != '<')
			&& (str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z')
			&& (str[i] < '0' || str[i] > '9') && check_in_quote(str, i) != 1)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int	nb_d_quotes(char *str)
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

int	nb_s_quotes(char *str)
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

int	syntax_quote(char *str)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	d = nb_d_quotes(str);
	s = nb_s_quotes(str);
	while (str[i] != '\0')
	{
		if (str[i] == 34)
		{
			i++;
			while ((str[i]) != 34 && str[i] != '\0')
			{
				if (str[i] == 39)
					s--;
				i++;
			}
		}
		else if (str[i] == 39)
		{
			i++;
			while ((str[i]) != 39 && str[i] != '\0')
			{
				if (str[i] == 34)
					d--;
				i++;
			}//return s et d
		}
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
	if (syntax_charac(str) == -1)
		return (0);
	if (syntax_red(str) == -1)
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
