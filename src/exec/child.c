/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:35:21 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/26 14:36:46 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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

static void	redir1(int *pipefd, t_pars *pars, int i, int nb_cmd)
{
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
}

void	child(int *pipefd, t_pars *pars, int i, char **envp)
{
	static int	nb_cmd;
	pid_t		pid;

	nb_cmd = count_cmd(pars);
	signal(SIGINT, handle_sigint_child);
	signal(SIGQUIT, handle_sigquit_child);
	pid = fork();
	if (pid == 0)
	{
		redir1(pipefd, pars, i, nb_cmd);
		if (pars->infile != -1)
		{
			if (pipefd)
				free(pipefd);
			exe_cmd(pars, envp);
		}
	}
}
