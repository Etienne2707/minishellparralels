/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:45 by educlos           #+#    #+#             */
/*   Updated: 2023/11/28 17:27:30 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	init_vars(char ***envpcpy, char **envp, t_wd **wd)
{
	*envpcpy = ft_cpy_double_array(envp);
	if (!(*envpcpy))
		return (EXIT_FAILURE);
	*wd = init_wd(*envpcpy);
	if (!(*wd))
	{
		ft_free_double_array(*envpcpy);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	minishell_loop(char **envp, t_pars *pars, t_token *token, t_wd *wd)
{
	char	*str;

	str = NULL;
	while (-1)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell$ ");
		if (!str)
			handle_ctrl_d(envp, wd);
		if (str && str[0] != 0)
		{
			add_history(str);
			if (check_str(str, token, envp, &pars) == 1)
			{
				add_wd(pars, wd);
				free(str);
				executor(pars, &envp, wd);
				ft_free_list(&pars);
				pars = NULL;
				printf("exit status : %d\n", g_exit_status);
			}
		}
	}
}

static void	start_minishell(char **envp)
{
	t_token	*token;
	t_pars	*pars;
	char	**envpcpy;
	t_wd	*wd;

	if (init_vars(&envpcpy, envp, &wd))
		exit(EXIT_FAILURE);
	token = NULL;
	pars = NULL;
	minishell_loop(envpcpy, pars, token, wd);
}

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	start_minishell(envp);
	return (1);
}
