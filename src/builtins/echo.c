/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:58:51 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/30 00:08:45 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	only_n_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	if (arg[i] == '-' && arg[i + 1] != 'n')
		return (0);
	i++;
	while (arg && arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	move_cursor_after_option(char **cmd, int *i)
{
	int	j;

	while (cmd && cmd[*i])
	{
		if (cmd[*i][0] != '-')
			return ;
		j = 1;
		while (cmd[*i][j] != 0)
		{
			if (cmd[*i][j] != 'n')
				return ;
			j++;
		}
		(*i)++;
	}
}

int	ft_echo(t_pars *pars)
{
	int	newline_bool;
	int	outfile;
	int	i;

	newline_bool = 1;
	outfile = 1;
	i = 1;
	if (pars->cmd[i] && only_n_arg(pars->cmd[i]))
	{
		newline_bool = 0;
		i++;
		move_cursor_after_option(pars->cmd, &i);
	}
	if (pars->outfile > 0)
		outfile = pars->outfile;
	while (pars->cmd[i])
	{
		ft_putstr_fd(pars->cmd[i], outfile);
		if (ft_strlen(pars->cmd[i]) != 0 && pars->cmd[i + 1] != NULL)
			ft_putstr_fd(" ", outfile);
		i++;
	}
	if (newline_bool)
		ft_putstr_fd("\n", outfile);
	return (EXIT_SUCCESS);
}
