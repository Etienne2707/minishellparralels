/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:07:02 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/14 09:38:17 by mle-duc          ###   ########.fr       */
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

static int	is_builtin(char **cmd_args, char **envp)
{
	if (ft_strncmp(cmd_args[0], "echo", 5) == 0)
		return (ft_echo(cmd_args));
	if (ft_strncmp(cmd_args[0], "env", 4) == 0)
		return (ft_env(envp));
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0)
		return (ft_exit(cmd_args));
	if (ft_strncmp(cmd_args[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd_args[0], "export", 7) == 0)
		return (ft_export(cmd_args, &envp));
	if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		return (ft_unset(cmd_args, &envp));
	return (-1000);
}

void	exe_cmd(char **cmd_args, char **envp)
{
	char	**path;
	char	*cmd_path;

	if (is_builtin(cmd_args, envp) != -1000)
		exit(0);
	if (find_char(cmd_args[0], '/'))
	{
		execve(cmd_args[0], cmd_args, envp);
		exit(127);
	}
	path = ft_split(find_path(envp), ':');
	cmd_path = get_right_cmd_path(path, cmd_args[0]);
	if (cmd_path == NULL)
	{
		ft_putstr_fd("Command not found\n", 2);
		free_tab(cmd_args);
		free_tab(path);
		exit(127);
	}
	execve(cmd_path, cmd_args, envp);
	exit(127);
}
/*
static void	init_pars(t_pars *pars, char *cmd, int outfile, int infile)
{
	pars->cmd = ft_split(cmd, ' ');
	pars->infile = infile;
	pars->outfile = outfile;
	pars->append = 0;
	pars->delimiter = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pars	*pars;
	t_pars	*pars2;
	t_pars	*pars3;

	int fd = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	pars = malloc(sizeof(t_pars));
	pars2 = malloc(sizeof(t_pars));
	pars3 = malloc(sizeof(t_pars));

	init_pars(pars, "cat -e", 0, fd);
	init_pars(pars2, "ls", 0, 0);
	init_pars(pars3, "sleep 10", 0 , 0);

	pars->next = pars2;
	pars2->next = pars3;
	pars3->next = NULL;

	executor(pars, envp);
	close(fd);
	free_tab(pars->cmd);
	free_tab(pars2->cmd);
	free_tab(pars3->cmd);
	free(pars);
	free(pars2);
	free(pars3);
	return (0);
}*/
