/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:55 by educlos           #+#    #+#             */
/*   Updated: 2023/11/27 08:34:59 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_heredoc_files(t_pars *pars)
{
	int		nb_cmd;
	int		i;
	char	*index;
	char	*file_name;

	nb_cmd = count_cmd(pars);
	i = 0;
	while (i < nb_cmd)
	{
		index = ft_itoa(i);
		if (!index)
			return ;
		file_name = ft_strjoin(".heredoc_tmp_", index);
		if (!file_name)
		{
			free(index);
			return ;
		}
		free(index);
		unlink(file_name);
		free(file_name);
		i++;
	}
}

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
	if (pars->infile > 0)
		close(pars->infile);
	free(pars);
}

void	ft_free_list(t_pars **pars)
{
	t_pars	*temp;

	while ((*pars)->prev != NULL)
		(*pars) = (*pars)->prev;
	unlink_heredoc_files(*pars);
	while (*pars != NULL)
	{
		temp = *pars;
		*pars = (*pars)->next;
		free_maillon(temp);
	}
}

void	free_remaining(t_pars *pars, char **envp)
{
	free((pars->wd)->pwd);
	free((pars->wd)->oldpwd);
	free(pars->wd);
	ft_free_double_array(envp);
	ft_free_list(&pars);
}
