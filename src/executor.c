/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:44:30 by mle-duc           #+#    #+#             */
/*   Updated: 2023/10/25 19:46:59 by mle-duc          ###   ########.fr       */
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
}

static void	child(int *pipefd, t_pars *pars, char *envp[], int i, int nb_cmd)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (i == 0)
		{
			dup2(pipefd[1], 1);
			if (pars->infile != 0 || pars->outfile != 0)
				redir_files(pars);
		}
		else if (i == nb_cmd - 1)
		{
			dup2(pipefd[2 * i - 2], 0);
			if (pars->infile != 0 || pars->outfile != 0)
				redir_files(pars);
		}
		else
		{
			redir(pipefd[2 * i - 2], pipefd[2 * i + 1]);
			if (pars->infile != 0 || pars->outfile != 0)
				redir_files(pars);
		}
		close_pipes(pipefd, nb_cmd);
		exe_cmd(pars->cmd, envp);
	}
}

int	executor(t_pars *pars, char *envp[])
{
	int	nb_of_cmd;
	int	*pipefd;
	int	i;

	nb_of_cmd = count_cmd(pars);
	pipefd = malloc(sizeof(int) * 2 * (nb_of_cmd - 1));
	if (!pipefd)
		return (EXIT_FAILURE);
	create_pipes(pipefd, nb_of_cmd);
	i = 0;
	while (i < nb_of_cmd)
	{
		child(pipefd, pars, envp, i++, nb_of_cmd);
		pars = pars->next;
	}
	close_pipes(pipefd, nb_of_cmd);
	i = 0;
	while (i < nb_of_cmd + 1)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	//waitpid(-1, NULL, 0);
	free(pipefd);
	return (0);
}


