/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:45 by educlos           #+#    #+#             */
/*   Updated: 2023/11/16 14:23:00 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(char *str, t_token *token, char **envp, t_pars **pars)
{
	int		i;
	char	**cmd;
	char	*dest;

	i = 0;
	dest = NULL;
	if (syntax_check(str) == 0)
		return (-1);
	dest = malloc_cpy(dest, str);
	dest = ft_dollars(dest, envp, dest);
	dest = add_space(dest);
	cmd = ft_split(dest, '|');
	if ((check_pipe(cmd, dest)) == -1)
		return (-1);
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
	if ((syntax_error(str, token, envp, pars)) == -1)
	{
		write(1, "Syntax Error\n", 13);
		return (-1);
	}
	return (1);
}

static int	init_vars(char ***envpcpy, char **envp, t_wd **wd)
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
	str = readline("Minishell > ");
	while (-1)
	{
		add_history(str);
		check_str(str, token, envpcpy, &pars);
		free(str);
		executor(pars, &envpcpy, wd);
		ft_free_list(&pars);
		pars = NULL;
		str = readline("Minishell > ");
	}
}

int	main(int ac, char **argv, char **envp)
{
	(void)ac;
	(void)argv;
	minishell_loop(envp);
	return (1);
}
