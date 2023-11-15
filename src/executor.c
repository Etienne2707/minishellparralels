/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:44:30 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 08:47:04 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_pipes(int *pipefd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < nb_of_cmd - 1)
	{
		if (pipe(pipefd + 2 * i) < 0)
			exit(EXIT_FAILURE);
		i++;
	}
}

static void	close_pipes(int *pipefd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < 2 *(nb_of_cmd - 1))
		close(pipefd[i++]);
}

static void	redir(int pipein, int pipeout)
{
	dup2(pipein, 0);
	dup2(pipeout, 1);
}

static void	redir_files(t_pars *pars)
{
	if (pars->infile != 0)
		dup2(pars->infile, 0);
	if (pars->outfile != 0)
		dup2(pars->outfile, 1);
	if (pars->infile == -1)
		ft_putstr_fd("minishell: No such file or directory: ", 2);
}

static void ft_heredoc(t_pars *pars, int *pipefd, int i, int nb_cmd)
{
	int		len;
	char	*line;
	int	j;

	j = 0;
	while (pars->delimiter[j] != NULL)
	{
		line = readline("> ");
		len = ft_strlen(pars->delimiter[j]);
		while (line && (ft_strncmp(line, pars->delimiter[j], len)))
		{
			if (i == 0)
			{
				write(0, line, ft_strlen(line));
				line = readline("> ");
			}
			else if (i != nb_cmd - 1)
			{
				write(pipefd[2 * i + 1], line, ft_strlen(line));
				line = readline("> ");
			}
		}
		free(line);
		j++;
	}
}

static void	child(int *pipefd, t_pars *pars,int i, int nb_cmd, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (pars->delimiter != NULL)
			ft_heredoc(pars, pipefd, i, nb_cmd);
		if (i == 0 && nb_cmd != 1)
		{
			dup2(pipefd[1], 1);
			if (pars->infile != 0 || pars->outfile != 0)
				redir_files(pars);
		}
		else if (i == nb_cmd - 1 && nb_cmd != 1)
		{
			dup2(pipefd[2 * i - 2], 0);
			if (pars->infile != 0 || pars->outfile != 0)
				redir_files(pars);
		}
		else if (nb_cmd != 1)
		{
			redir(pipefd[2 * i - 2], pipefd[2 * i + 1]);
			if (pars->infile != 0 || pars->outfile != 0)
				redir_files(pars);
		}
		close_pipes(pipefd, nb_cmd);
		if (pars->infile != -1)
			exe_cmd(pars->cmd, envp);
	}
}

static int	is_builtin(char **cmd_args)
{
	if (ft_strncmp(cmd_args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		return (1);
	return (0);
}

static int	exe_builtin(char **cmd_args, char ***envp, t_wd *wd)
{
	if (ft_strncmp(cmd_args[0], "echo", 5) == 0)
		return (ft_echo(cmd_args));
	if (ft_strncmp(cmd_args[0], "env", 4) == 0)
		return (ft_env(*envp));
	if (ft_strncmp(cmd_args[0], "exit", 5) == 0)
		return (ft_exit(cmd_args));
	if (ft_strncmp(cmd_args[0], "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd_args[0], "export", 7) == 0)
		return (ft_export(cmd_args, envp));
	if (ft_strncmp(cmd_args[0], "unset", 5) == 0)
		return (ft_unset(cmd_args, envp));
	if (ft_strncmp(cmd_args[0], "cd", 2) == 0)
		return (ft_cd(cmd_args, envp, wd));
	return (-1000);
}

int	executor(t_pars *pars, char ***envp, t_wd *wd)
{
	int	nb_of_cmd;
	int	*pipefd;
	int	i;

	nb_of_cmd = count_cmd(pars);
	if (nb_of_cmd == 1 && is_builtin(pars->cmd))
	{
		exe_builtin(pars->cmd, envp, wd);
		return (0);
	}
	pipefd = malloc(sizeof(int) * 2 * (nb_of_cmd - 1));
	if (!pipefd)
		return (EXIT_FAILURE);
	create_pipes(pipefd, nb_of_cmd);
	i = 0;
	while (i < nb_of_cmd)
	{
		child(pipefd, pars, i++, nb_of_cmd, *envp);
		pars = pars->next;
	}
	close_pipes(pipefd, nb_of_cmd);
	i = -1;
	while (++i < nb_of_cmd + 1)
		waitpid(-1, NULL, 0);
	free(pipefd);
	return (0);
}


