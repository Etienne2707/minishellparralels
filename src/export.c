/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:49:03 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/14 16:15:40 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, char ***envp)
{
	int		i;
	char	**temp;

	if (!args[1] || args[1][0] == 0)
		return (EXIT_FAILURE); //rajouter print du env avec les declare -x
	else
	{
		i = 1;
		while (args[i])
		{
			if (check_param(args[i]) == 0
				&& var_already_exists(*envp, args[i]) == 0)
			{
				temp = ft_append_double_array(*envp, args[i]);
				ft_free_double_array(*envp);
				*envp = temp;
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/*
int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	char	**envpcpy;
	char	**new_envp;
	char	**ok;


	i = 0;
	envpcpy = ft_cpy_double_array(envp);
	
	new_envp = ft_append_double_array(envpcpy, "ok slt test");
	while (new_envp[i])
	{
		printf("%s\n", new_envp[i]);
		i++;
	}
	ft_free_double_array(envpcpy);

	ft_export(argv, &envpcpy);
	while (envpcpy[i])
	{
		printf("%s\n", envpcpy[i]);
		i++;
	}

	return (0);
}*/
