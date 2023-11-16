/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:42:19 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/16 11:53:30 by mle-duc          ###   ########.fr       */
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

void	print_list(t_pars **pars)
{
	t_pars	*current;
	int		i;

	current = *pars;
	while (current != NULL)
	{
		i = 0;
		while (current->cmd[i] != NULL)
		{
			printf("cmdlist = %s   ", current->cmd[i]);
			i++;
		}
		printf("\noutfile = %d \n", current->outfile);
		printf("infile = %d\n", current->infile);
		if (current->delimiter != NULL)
		{
			i = 0;
			while (current->delimiter[i] != NULL)
			{
				printf("heredoc = %s\n", current->delimiter[i]);
				i++;
			}
		}
		current = current->next;
	}
}
