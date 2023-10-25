/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 12:50:33 by mle-duc           #+#    #+#             */
/*   Updated: 2023/10/25 19:47:31 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_status(int status)
{
	if (WEXITSTATUS(status) == 127)
		exit(127);
	else if (WEXITSTATUS(status) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
}

void	print_err(char *str)
{
	ft_printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
