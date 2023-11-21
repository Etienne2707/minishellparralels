/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:49:03 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/21 13:01:15 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export2(char **args, char ***envp, int *exitvalue, int i)
{
	char	**temp;
	int		check_par;

	check_par = check_param(args[i]);
	if (check_par == -1)
		return (EXIT_SUCCESS);
	if (check_par == 0 && var_already_exists(*envp, args[i]) == 0)
	{
		temp = ft_append_double_array(*envp, args[i]);
		if (!temp)
			return (EXIT_FAILURE);
		ft_free_double_array(*envp);
		*envp = temp;
	}
	else if (!(*exitvalue))
		*exitvalue = EXIT_FAILURE;
	return (EXIT_SUCCESS);
}

int	ft_export(char **args, char ***envp)
{
	int		i;
	int		exitvalue;

	exitvalue = EXIT_SUCCESS;
	if (!args[1] || args[1][0] == 0)
		ft_env(*envp);
	else
	{
		i = 1;
		while (args[i])
		{
			if (ft_export2(args, envp, &exitvalue, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
	}
	return (exitvalue);
}
