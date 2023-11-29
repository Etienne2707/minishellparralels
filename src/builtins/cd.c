/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:43:06 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/29 02:54:48 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	err_msg(char **cmd)
{
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(cmd[1], 1);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static void	refresh(t_wd *wd, char ***envp)
{
	refresh_wd(wd, envp);
	refresh_env(wd, envp);
}

static int	check_cd_args(char **cmd)
{
	if (cmd[1])
	{
		if (cmd[1][0] == '-' && cmd[1][1] != 0
			&& cmd[1][1] != '-')
		{
			ft_putstr_fd("minishell: cd: -", 2);
			ft_putchar_fd(cmd[1][1], 2);
			ft_putstr_fd(": invalid option\n", 2);
			return (0);
		}
		if (cmd[1][0] == '-' && cmd[1][1] == '-'
				&& cmd[1][2] != 0)
		{
			ft_putstr_fd("minishell: pwd: --: invalid option\n", 2);
			return (0);
		}
	}
	return (1);
}

int	ft_cd(char **cmd, char ***envp, t_wd *wd)
{
	int	path;

	if (!cmd[1] || (cmd[1][0] == '-' && cmd[1][1] == '-'
		&& cmd[1][2] == 0 && cmd[2] == NULL))
		path = get_path(*envp, "HOME=");
	else if (cmd[1][0] == '-' && cmd[1][1] == 0)
		path = get_path(*envp, "OLDPWD=");
	else if (!check_cd_args(cmd))
		return (2);
	else if (cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	else
	{
		path = chdir(cmd[1]);
		if (path)
			err_msg(cmd);
	}
	if (path)
		return (EXIT_FAILURE);
	if (wd)
		refresh(wd, envp);
	return (EXIT_SUCCESS);
}
