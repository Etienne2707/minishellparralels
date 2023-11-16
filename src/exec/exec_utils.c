/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:53:22 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 13:57:30 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char **cmd_args)
{
	if (ft_strncmp(cmd_args[0], "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "exit", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "export", 6) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		return (1);
	return (0);
}

static int	exe_builtin(t_pars *pars, char ***envp, t_wd *wd)
{
	if (ft_strncmp(pars->cmd[0], "echo", 4) == 0)
		return (ft_echo(pars->cmd));
	if (ft_strncmp(pars->cmd[0], "env", 3) == 0)
		return (ft_env(*envp));
	if (ft_strncmp(pars->cmd[0], "exit", 4) == 0)
		return (ft_exit(pars, pars->cmd, *envp, wd));
	if (ft_strncmp(pars->cmd[0], "pwd", 3) == 0)
		return (ft_pwd());
	if (ft_strncmp(pars->cmd[0], "export", 6) == 0)
		return (ft_export(pars->cmd, envp));
	if (ft_strncmp(pars->cmd[0], "unset", 5) == 0)
		return (ft_unset(pars->cmd, envp));
	if (ft_strncmp(pars->cmd[0], "cd", 2) == 0)
		return (ft_cd(pars->cmd, envp, wd));
	return (EXIT_FAILURE);
}

int	exec_single(t_pars *pars, int nb_cmd, char ***envp, t_wd *wd)
{
	if (nb_cmd == 0 && pars->delimiter != NULL)
		ft_heredoc(pars, NULL, 0);
	if (nb_cmd == 1 && is_builtin(pars->cmd))
	{
		if (pars->delimiter != NULL)
			ft_heredoc(pars, NULL, 0);
		exe_builtin(pars, envp, wd);
		return (1);
	}
	return (0);
}