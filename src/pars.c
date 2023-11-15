/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:42:19 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/15 09:06:53 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_pars *pars)
{
	int		nb_of_cmd;
	t_pars	*temp;

	nb_of_cmd = 0;
	temp = pars;
	while (temp != NULL && temp->cmd[0] != NULL)
	{
		nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}
