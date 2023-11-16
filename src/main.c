/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:45 by educlos           #+#    #+#             */
/*   Updated: 2023/11/16 12:31:57 by mle-duc          ###   ########.fr       */
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

int	main(int ac, char **argv, char **envp)
{
	t_token	*token;
	t_pars	*pars;
	char	*str;
	char	**envpcpy;
	t_wd	*wd;

	(void)ac;
	(void)argv;
	envpcpy = ft_cpy_double_array(envp);
	wd = init_wd(envpcpy);
	if (!wd)
		return (EXIT_FAILURE);
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
	return (1);
}
