/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:35:08 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 13:35:41 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_pars *pars, char *envp[])
{
	int	i;
	int	outfile;

	outfile = 1;
	if (pars->outfile > 0)
		outfile = pars->outfile;
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], outfile);
		ft_putstr_fd("\n", outfile);
		i++;
	}
	return (EXIT_SUCCESS);
}
