/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:07:02 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/17 18:01:42 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	is_builtin(char **cmd_args, char **envp, int *exit_code)
{
	*exit_code = EXIT_FAILURE;
	if (ft_strncmp(cmd_args[0], "echo", 5) == 0)
		*exit_code = ft_echo(cmd_args);
	if (ft_strncmp(cmd_args[0], "env", 4) == 0)
		*exit_code = ft_env(envp);
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0)
		*exit_code = EXIT_SUCCESS;
	if (ft_strncmp(cmd_args[0], "pwd", 4) == 0)
		*exit_code = ft_pwd();
	if (ft_strncmp(cmd_args[0], "export", 7) == 0)
		*exit_code = ft_export(cmd_args, &envp);
	if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		*exit_code = ft_unset(cmd_args, &envp);
	if (ft_strncmp(cmd_args[0], "cd", 3) == 0)
		*exit_code = ft_cd(cmd_args, &envp, NULL);
	return (*exit_code);
}

static void	free_remaining(t_pars *pars, char **envp)
{
	free((pars->wd)->pwd);
	free((pars->wd)->oldpwd);
	free(pars->wd);
	ft_free_double_array(envp);
	ft_free_list(&pars);
}

void	exe_cmd(t_pars *pars, char **envp)
{
	char	**path;
	char	*cmd_path;
	int		exit_code;

	if (is_builtin(pars->cmd, envp, &exit_code) != EXIT_FAILURE)
	{
		free_remaining(pars, envp);
		exit(exit_code);
	}
	if (find_char(pars->cmd[0], '/'))
	{
		execve(pars->cmd[0], pars->cmd, envp);
		exit(127);
	}
	path = ft_split_lib(find_path(envp), ':');
	cmd_path = get_right_cmd_path(path, pars->cmd[0]);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		free_remaining(pars, envp);
		free_tab(path);
		exit(127);
	}
	execve(cmd_path, pars->cmd, envp);
	exit(127);
}
