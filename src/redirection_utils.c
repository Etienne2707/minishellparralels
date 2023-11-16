/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:32 by educlos           #+#    #+#             */
/*   Updated: 2023/11/16 11:46:50 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_outfile(t_token *token, char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != 0)
	{
		if (ft_strcmp(arg[i], ">") == 0 || ft_strcmp(arg[i], ">>") == 0)
			token->last_o = i;
		i++;
	}
	return (token->last_o);
}

int	nb_infile(t_token *token, char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != 0)
	{
		if (ft_strcmp(arg[i], "<") == 0)
			token->last_i = i;
		i++;
	}
	return (token->last_i);
}

void	get_infile(t_token *token, char **arg, int i)
{
	int	fd;

	if (token->infile == -1)
		return ;
	fd = open(arg[i], O_RDONLY);
	token->infile = fd;
	if (i - 1 == token->last_i)
	{
		return ;
	}
	close(fd);
}

void	get_outfile(t_token *token, char **arg, int i)
{
	int	fd;

	if (token->outfile == -1)
		return ;
	fd = open(arg[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	token->outfile = fd;
	token->append = 0;
	if (i - 1 == token->last_o)
	{
		return ;
	}
	close(fd);
}
