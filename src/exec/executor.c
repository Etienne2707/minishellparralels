/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:44:30 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 18:10:31 by mle-duc          ###   ########.fr       */
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

void	close_pipes(int *pipefd, int nb_of_cmd)
{
	int	i;

	i = 0;
	while (i < 2 *(nb_of_cmd - 1))
		close(pipefd[i++]);
}

void	wait_and_close(int *pipefd, int nb_cmd)
{
	int	i;

	i = 0;
	close_pipes(pipefd, nb_cmd);
	while (i < nb_cmd)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	if (pipefd)
		free(pipefd);
}

int	executor(t_pars *pars, char ***envp, t_wd *wd)
{
	int	*pipefd;
	int	i;
	int	nb_cmd;

	nb_cmd = count_cmd(pars);
	if (exec_single(pars, nb_cmd, envp, wd))
		return (0);
	pipefd = NULL;
	if (nb_cmd > 1)
	{
		pipefd = malloc(sizeof(int) * 2 * (nb_cmd - 1));
		if (!pipefd)
			return (EXIT_FAILURE);
	}
	create_pipes(pipefd, nb_cmd);
	i = -1;
	while (++i < nb_cmd)
	{
		if (pars->delimiter != NULL)
			ft_heredoc(pars, pipefd, i);
		child(pipefd, pars, i, *envp);
		pars = pars->next;
	}
	wait_and_close(pipefd, nb_cmd);
	return (0);
}
