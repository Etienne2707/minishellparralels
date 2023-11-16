/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:27:00 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 14:14:54 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_free_double_array(envp);
	free(wd->pwd);
	free(wd->oldpwd);
	free(wd);
	ft_free_list(&pars);
}

int	ft_exit(t_pars *pars, char **args, char **envp, t_wd *wd)
{
	int	exit_code;

	if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) != 0)
		return (EXIT_FAILURE);
	if (args[1])
		exit_code = ft_atoi(args[1]);
	exit_code = 1;
	//else
	//	exit_code = get_err_code();
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (args[1] && (!is_arg_valid(args[1]) || ft_strlen(args[1]) > 19))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit(2);
	}
	ft_putstr_fd("exit\n", STDERR_FILENO);
	free_everything(pars, envp, wd);
	exit(exit_code);
}
