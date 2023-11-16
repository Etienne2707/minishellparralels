/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:49:03 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 14:10:34 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char **args, char ***envp)
{
	int		i;
	char	**temp;

	if (!args[1] || args[1][0] == 0)
		ft_env(*envp);
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
