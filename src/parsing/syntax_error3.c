/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:15:42 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 09:13:44 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_tab(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (str[i] != '\0')
	{
		if (str[i] < 9 || str[i] > 13)
			result = 0;
		i++;
	}
	if (ft_strcmp(str, ":") == 0)
		return (1);
	return (result);
}

int	syntax_error(char *str, t_token *token, char **envp, t_pars **pars)
{
	char	**cmd;
	char	*dest;

	dest = NULL;
	if (syntax_check(str) == 0)
		return (-1);
	if (only_tab(str) == 1)
		return (2);
	dest = malloc_cpy(dest, str);
	dest = ft_dollars(str, envp, dest);
	if (!dest)
		return (-1);
	if (syntax_check(dest) == 0)
	{
		free(dest);
		return (-1);
	}
	dest = add_space(dest);
	cmd = ft_split(dest, '|');
	if ((check_pipe(cmd, dest)) == -1)
		return (-1);
	free(dest);
	init_struct(cmd, token, pars);
	ft_free_double_array(cmd);
	return (1);
}

int	check_str(char *str, t_token *token, char **envp, t_pars **pars)
{
	int	result;

	result = syntax_error(str, token, envp, pars);
	if (result == -1)
	{
		return (-1);
	}
	else if (result == 2)
	{
		ft_putstr_fd("", 2);
		return (-1);
	}
	return (1);
}

int	is_n_a(char c)
{
	if (c == 34 || c == 39)
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else if (c == '?')
		return (1);
	else
		return (-1);
}

int	check_pipe2(char **cmd)
{
	int	i;
	int	k;
	int	c;

	i = 0;
	while (cmd[i] != 0)
	{
		k = 0;
		c = 0;
		while (cmd[i][k] != 0)
		{
			if (cmd[i][k] != ' ')
				c++;
			k++;
		}
		if (c == 0)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
			return (-1);
		}
		i++;
	}
	return (1);
}
