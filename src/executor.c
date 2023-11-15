/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:44:30 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 18:03:06 by mle-duc          ###   ########.fr       */
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

static void ft_heredoc(t_pars *pars, int *pipefd, int i)
{
	int		len;
	char	*line;
	int	j;
	int	fd;

	j = 0;
	while (pars->delimiter[j] != NULL)
	{
		line = readline("> ");
		len = ft_strlen(pars->delimiter[j]);
		if (i == 0)
		{
			fd = open (".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
				exit(EXIT_FAILURE);
		}
		while (line && (ft_strncmp(line, pars->delimiter[j], len)))
		{
			if (i == 0)
			{
				write(fd, line, ft_strlen(line));
				write(fd, "\n", 1);
				line = readline("> ");
			}
			else
			{
				write(pipefd[2 * (i - 1) + 1], line, ft_strlen(line));
				write(pipefd[2 * (i - 1) + 1], "\n", 1);
				line = readline("> ");
			}
		}
		free(line);
		j++;
		close(fd);
	}
	if (!pars->infile)
		pars->infile = open(".heredoc_tmp", O_RDONLY);
}

static void	child(int *pipefd, t_pars *pars,int i, int nb_cmd, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (pars->next != NULL && (pars->next)->delimiter != NULL)
			exit(1);
		if (pars->delimiter != NULL)
			ft_heredoc(pars, pipefd, i);
		if (i == 0)
		{
			if (nb_cmd != 1)
				dup2(pipefd[1], 1);
			redir_files(pars);
		}
		else if (i == nb_cmd - 1 && nb_cmd != 1)
		{
			dup2(pipefd[2 * i - 2], 0);
			redir_files(pars);
		}
		else if (nb_cmd != 1)
		{
			redir(pipefd[2 * i - 2], pipefd[2 * i + 1]);
			redir_files(pars);
		}
		close_pipes(pipefd, nb_cmd);
		if (pars->infile != -1)
			exe_cmd(pars->cmd, envp);
	}
}

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

int	executor(t_pars *pars, char ***envp, t_wd *wd)
{
	int	nb_of_cmd;
	int	*pipefd;
	int	i;

	nb_of_cmd = count_cmd(pars);
	if (nb_of_cmd == 0 && pars->delimiter != NULL)
		ft_heredoc(pars, NULL, 0);
	if (nb_of_cmd == 1 && is_builtin(pars->cmd))
	{
		exe_builtin(pars, envp, wd);
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


