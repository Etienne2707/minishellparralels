/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:45 by educlos           #+#    #+#             */
/*   Updated: 2023/11/26 10:48:08 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	only_tab(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (str[i] != '\0')
	{
		if (str[i] < 9 || str[i] > 13)
			result = 0;
		i++;
	}
	if (ft_strcmp(str, ":") == 0)
		return (1);
	return (result);
}

int	syntax_error(char *str, t_token *token, char **envp, t_pars **pars)
{
	int		i;
	char	**cmd;
	char	*dest;

	i = 0;
	dest = NULL;
	if (syntax_check(str) == 0)
		return (-1);
	if (only_tab(str) == 1)
		return (2);
	dest = malloc_cpy(dest, str);
	dest = ft_dollars(str, envp, dest);
	dest = add_space(dest);
	cmd = ft_split(dest, '|');
	if (cmd == NULL)
	{
		printf("CMD NULL");
		return (-1);
	}
	if ((check_pipe(cmd, dest)) == -1)
	{
		printf("check pipe");
		return (-1);
	}
	free(dest);
	init_struct(cmd, token, pars);
	while (cmd[i] != 0)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (1);
}

int	check_str(char *str, t_token *token, char **envp, t_pars **pars)
{
	int	result;

	result = syntax_error(str, token, envp, pars);
	if (result == -1)
	{
		ft_putstr_fd("minishell: syntax_error\n", 2);
		return (-1);
	}
	else if (result == 2)
	{
		ft_putstr_fd("", 2);
		return (-1);
	}
	return (1);
}

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

static void	minishell_loop(char **envp)
{
	t_token	*token;
	t_pars	*pars;
	char	*str;
	char	**envpcpy;
	t_wd	*wd;

	if (init_vars(&envpcpy, envp, &wd))
		exit(EXIT_FAILURE);
	str = NULL;
	pars = NULL;
	token = NULL;
	while (-1)
	{
		signal(SIGINT, &handle_sigint);
		signal(SIGQUIT, SIG_IGN);
//		printf("exit status : %d\n", g_exit_status);
		str = readline("Minishell > ");
		if (!str)
			handle_ctrl_d(envpcpy, wd);
		if (str && str[0] != 0)
		{
			add_history(str);
			if (check_str(str, token, envpcpy, &pars) == 1)
			{
				add_wd(pars, wd);
				free(str);
				executor(pars, &envpcpy, wd);
				ft_free_list(&pars);
				pars = NULL;
			}
		}
	}
}

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	minishell_loop(envp);
	return (1);
}
