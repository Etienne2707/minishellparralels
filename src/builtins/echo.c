/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:58:51 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/14 09:12:52 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	newline_bool;

	newline_bool = 1;
	if (ft_strncmp(*args, "echo", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args && ft_strncmp(*args, "-n", 3) == 0)
	{
		newline_bool = 0;
		args++;
	}
	while (*args)
	{
		if (printf("%s", *args) != (int)ft_strlen(*args))
			return (EXIT_FAILURE);
		if (ft_strlen(*args) != 0 && *(args + 1) != NULL)
			if (printf(" ") != (int)ft_strlen(" "))
				return (EXIT_FAILURE);
		args++;
	}
	if (newline_bool)
		if (printf("\n") != (int)ft_strlen("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
