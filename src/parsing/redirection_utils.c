/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:32 by educlos           #+#    #+#             */
/*   Updated: 2023/11/28 12:43:13 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

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
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[i], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
	}
	token->infile = fd;
	if (i - 1 == token->last_i)
		return ;
	if (fd != -1)
		close(fd);
}

void	get_outfile(t_token *token, char **arg, int i)
{
	int	fd;

	if (token->outfile == -1)
		return ;
	fd = open(arg[i], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (access(arg[i], W_OK) != 0)
	{
		token->outfile = -1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[i], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 1;
	}
	else
		token->outfile = fd;
	token->append = 0;
	if (i - 1 == token->last_o)
	{
		return ;
	}
	close(fd);
}
