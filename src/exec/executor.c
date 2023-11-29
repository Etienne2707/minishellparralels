/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:44:30 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/29 04:13:46 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	*create_pipes(int nb_of_cmd)
{
	int	i;
	int	*pipefd;

	pipefd = NULL;
	if (nb_of_cmd > 1)
	{
		pipefd = malloc(sizeof(int) * 2 * (nb_of_cmd - 1));
		if (!pipefd)
			exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < nb_of_cmd - 1)
	{
		if (pipe(pipefd + 2 * i) < 0)
		{
			free(pipefd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipefd);
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
	int	status;

	i = 0;
	status = 0;
	close_pipes(pipefd, nb_cmd);
	while (i < nb_cmd)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && g_exit_status != -1)
			g_exit_status = WEXITSTATUS(status);
		i++;
	}
	if (pipefd)
		free(pipefd);
}

static void	launch_heredoc(t_pars *pars, int *pipefd, int nb_cmd)
{
	t_pars	*tmp;
	int		i;

	i = 0;
	tmp = pars;
	while (i < nb_cmd)
	{
		if (tmp->delimiter != NULL && tmp->delimiter[0] != 0)
			ft_heredoc(tmp, pipefd, i);
		tmp = tmp->next;
		i++;
	}
}

int	executor(t_pars *pars, char ***envp, t_wd *wd)
{
	int	*pipefd;
	int	i;
	int	nb_cmd;
	int	boolean;

	boolean = 0;
	if (g_exit_status == -1)
		boolean = 1;
	nb_cmd = count_cmd(pars);
	if (exec_single(pars, nb_cmd, envp, wd))
		return (0);
	pipefd = create_pipes(nb_cmd);
	launch_heredoc(pars, pipefd, nb_cmd);
	i = -1;
	while (++i < nb_cmd && (g_exit_status != -1 || boolean))
	{
		if (pars)
			child(pipefd, pars, i, *envp);
		pars = pars->next;
	}
	wait_and_close(pipefd, nb_cmd);
	return (0);
}
