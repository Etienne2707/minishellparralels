/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:16:58 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 13:51:50 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_error(char *current_wd)
{
	free(current_wd);
	current_wd = NULL;
	perror("\nError : write failed");
	return (EXIT_FAILURE);
}

int	ft_pwd(t_pars *pars)
{
	char	*current_wd;
	int		outfile;

	outfile = 1;
	if (pars->outfile)
		outfile = pars->outfile;
	current_wd = NULL;
	current_wd = getcwd(current_wd, 0);
	if (current_wd == NULL)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	if (ft_putstr_fd(current_wd, outfile) == EXIT_FAILURE)
		return (free_error(current_wd));
	if (ft_putstr_fd("\n", outfile) == EXIT_FAILURE)
		return (free_error(current_wd));
	free(current_wd);
	current_wd = NULL;
	return (EXIT_SUCCESS);
}
