/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:02:44 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/24 17:16:11 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
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
