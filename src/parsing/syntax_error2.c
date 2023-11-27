/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:06:59 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 11:48:48 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	nb_d_quotes(char *str)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str && str[i] != '\0')
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
	while (str && str[i] != '\0')
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
		if (i > ft_strlen(str))
			break ;
	}
	if ((d % 2 != 0) || (s % 2 != 0))
		return (0);
	return (1);
}

int	syntax_check(char *str)
{
	if (syntax_quote(str) == 0)
	{
		ft_putstr_fd("minishell: syntax_error\n", 2);
		g_exit_status = 2;
		return (0);
	}
	if (syntax_red(str) == -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token \n", 2);
		g_exit_status = 2;
		return (0);
	}
	if (syntax_charac(str) == -1)
	{
		ft_putstr_fd("minishell: syntax error\n", 2);
		g_exit_status = 2;
		return (0);
	}
	return (1);
}

int	check_pipe(char **cmd, char *str)
{
	if (!str)
	{
		free(str);
		return (-1);
	}
	if (check_start_end(str) == -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		g_exit_status = 2;
		return (-1);
	}
	return (check_pipe2(cmd));
}
