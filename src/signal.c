/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:02:44 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 07:54:44 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exit_status != -1)
		{
			write(1, "\n", 1);
			g_exit_status = 130;
		}
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

void	handle_ctrl_d(char **envpcpy, t_wd *wd)
{
	ft_free_double_array(envpcpy);
	free(wd->pwd);
	free(wd->oldpwd);
	free(wd);
	ft_putstr_fd("exit\n", 2);
	exit(EXIT_SUCCESS);
}

void	handle_sigint_child(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
	}
}

void	handle_sigquit_child(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 19);
		g_exit_status = 131;
	}
}

void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = -1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		close(STDIN_FILENO);
	}
}
