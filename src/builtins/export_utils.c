/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 18:38:51 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/21 12:40:55 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i + j] == c)
				j++;
			ft_strlcpy(&str[i], &str[i + j], strlen(str) - i);
		}
		i++;
	}
	return (str);
}

int	after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	check_valid_identifier(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '[' || c == ']'
		|| c == '\'' || c == '\"' || c == ' ' || c == ',' || c == '.'
		|| c == ':' || c == '/' || c == '{' || c == '}' || c == '+'
		|| c == '^' || c == '%' || c == '#' || c == '@' || c == '!'
		|| c == '~'
		|| c == '=' || c == '-' || c == '?' || c == '&' || c == '*');
}

int	var_already_exists(char **envp, char *str)
{
	int	i;

	i = 0;
	if (str[after_equal(str)] == '\"')
		remove_quotes(str, '\"');
	if (str[after_equal(str)] == '\'')
		remove_quotes(str, '\'');
	while (envp[i])
	{
		if (ft_strncmp(envp[i], str, after_equal(envp[i])) == 0)
		{
			free(envp[i]);
			envp[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_param(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_err(str));
	while (str[i] != '=' && str[i])
	{
		if (check_valid_identifier(str[i]))
			return (export_err(str));
		i++;
	}
	i = 0;
	if (after_equal(str) == 0)
	{
		while (str[i])
		{
			if (check_valid_identifier(str[i]))
				return (export_err(str));
			i++;
		}
		return (-1);
	}
	if (str[0] == '=')
		return (export_err(str));
	return (EXIT_SUCCESS);
}
