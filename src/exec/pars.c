/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:42:19 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/24 17:48:03 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_pars *pars)
{
	int		nb_of_cmd;
	t_pars	*temp;

	nb_of_cmd = 0;
	temp = pars;
	while (temp != NULL && (temp->cmd[0] != NULL
			|| (temp->delimiter && temp->delimiter[0] != NULL)))
	{
		nb_of_cmd++;
		temp = temp->next;
	}
	return (nb_of_cmd);
}

void	print_list(t_pars **pars)
{
	t_pars	*current;
	int		i;

	current = *pars;
	while (current != NULL)
	{
		i = 0;
		while (current->cmd[i])
		{
			printf("cmd[%d] = %s\n", i, current->cmd[i]);
			i++;
		}
		printf("outfile = %d\n", current->outfile);
		printf("infile = %d\n", current->infile);
		i = 0;
		while (current->delimiter && current->delimiter[i] != 0)
		{
			printf("delimiter : %s\n", current->delimiter[i++]);
		}
		current = current->next;
	}
}
