/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:16:58 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/06 18:34:53 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*current_wd;

	current_wd = NULL;
	current_wd = getcwd(current_wd, 0);
	if (current_wd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	else if (printf("%s\n", current_wd) != (int)ft_strlen(current_wd) + 1)
	{
		free(current_wd);
		current_wd = NULL;
		perror("\nError : printf failed");
		return (EXIT_FAILURE);
	}
	free(current_wd);
	current_wd = NULL;
	return (EXIT_SUCCESS);
}
