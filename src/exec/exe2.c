/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:07:02 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/29 03:32:35 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	is_builtin(char **cmd_args, char **envp, int *exit, t_pars *pars)
{
	*exit = -1;
	if (!cmd_args || cmd_args[0] == 0)
		return (*exit);
	if (ft_strncmp(cmd_args[0], "echo", 5) == 0)
		*exit = ft_echo(pars);
	if (ft_strncmp(cmd_args[0], "env", 4) == 0)
		*exit = ft_env(pars, envp);
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0)
		*exit = EXIT_SUCCESS;
	if (ft_strncmp(cmd_args[0], "pwd", 4) == 0)
		*exit = ft_pwd(pars);
	if (ft_strncmp(cmd_args[0], "export", 7) == 0)
		*exit = ft_export(pars, cmd_args, &envp, 1);
	if (ft_strncmp(cmd_args[0], "unset", 6) == 0)
		*exit = ft_unset(cmd_args, &envp);
	if (ft_strncmp(cmd_args[0], "cd", 3) == 0)
		*exit = ft_cd(cmd_args, &envp, NULL);
	return (*exit);
}

static void	exe_err(t_pars *pars, char **envp, char **path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(pars->cmd[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_remaining(pars, envp);
	ft_free_double_array(path);
	exit(127);
}

void	exe_cmd(t_pars *pars, char **envp)
{
	char	**path;
	char	*cmd_path;
	int		exit_code;

	if (is_builtin(pars->cmd, envp, &exit_code, pars) != -1)
	{
		free_remaining(pars, envp);
		exit(exit_code);
	}
	if (find_char(pars->cmd[0], '/'))
		exe_relative(pars, envp);
	path = ft_split_lib(find_path(envp), ':');
	cmd_path = get_right_cmd_path(path, pars->cmd[0]);
	if (cmd_path == NULL)
		exe_err(pars, envp, path);
	execve(cmd_path, pars->cmd, envp);
	exit(127);
}
