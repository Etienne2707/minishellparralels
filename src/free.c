/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:55 by educlos           #+#    #+#             */
/*   Updated: 2023/11/15 21:47:01 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_maillon(t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->cmd[i] != 0)
	{
		free(pars->cmd[i]);
		i++;
	}
	free(pars->cmd);
	i = 0;
	if (pars->delimiter != NULL)
	{
		while (pars->delimiter[i] != NULL)
		{
			free(pars->delimiter[i]);
			i++;
		}
	}
	if (pars->delimiter)
		free(pars->delimiter);
	free(pars);
}

void	ft_free_list(t_pars **pars)
{
	t_pars	*next;

	if (*pars == NULL)
		return ;
	next = (*pars)->next;
	free_maillon((*pars));
	ft_free_list(&next);
}
