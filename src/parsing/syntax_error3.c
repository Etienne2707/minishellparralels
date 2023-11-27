/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:15:42 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/26 20:27:26 by mle-duc          ###   ########.fr       */
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
	int		i;
	char	**cmd;
	char	*dest;

	i = 0;
	dest = NULL;
	if (syntax_check(str) == 0)
		return (-1);
	if (only_tab(str) == 1)
		return (2);
	dest = malloc_cpy(dest, str);
	dest = ft_dollars(str, envp, dest);
	if (!dest)
		return (-1);
	dest = add_space(dest);
	cmd = ft_split(dest, '|');
	if ((check_pipe(cmd, dest)) == -1)
		return (-1);
	free(dest);
	init_struct(cmd, token, pars);
	while (cmd[i] != 0)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
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

int is_n_a(char c)
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
