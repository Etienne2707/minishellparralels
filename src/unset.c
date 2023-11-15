/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:15:08 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/14 15:55:45 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char ***envp)
{
	char	**tmp;
	int		i;

	i = 1;
	while (args[i])
	{
		if (var_exists(*envp, args[i]))
		{
			tmp = ft_pop_double_array(*envp, args[i]);
			ft_free_double_array(*envp);
			*envp = tmp;
		}
		i++;
	}
	i = 0;
	return (EXIT_SUCCESS);
}