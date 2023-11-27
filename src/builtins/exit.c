/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:27:00 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 23:26:12 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	is_arg_valid(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	free_everything(t_pars *pars, char **envp, t_wd *wd)
{
	(void)wd;
	ft_free_double_array(envp);
	free((pars->wd)->pwd);
	free((pars->wd)->oldpwd);
	free(pars->wd);
	ft_free_list(&pars);
}

int	ft_exit(t_pars *pars, char **args, char **envp, t_wd *wd)
{
	int	exit_code;

	if (args[1])
		exit_code = ft_atoi(args[1]);
	else
		exit_code = g_exit_status;
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (args[1] && (!is_arg_valid(args[1]) || ft_strlen(args[1]) > 19))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		free_everything(pars, envp, wd);
		exit(2);
	}
	ft_putstr_fd("exit\n", 1);
	free_everything(pars, envp, wd);
	exit(exit_code);
}
