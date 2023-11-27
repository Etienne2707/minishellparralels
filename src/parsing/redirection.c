/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:45:25 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 13:55:40 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	put_heredoc(t_token *token, char **arg)
{
	int	i;
	int	nbh;

	i = 0;
	nbh = 0;
	while (arg[i] != 0)
	{
		if (ft_strcmp("<<", arg[i]) == 0)
		{
			arg[i + 1] = ft_remove_quote(arg[i + 1]);
			token->delimiter[nbh++] = arg[i + 1];
		}
		i++;
	}
	token->delimiter[nbh] = 0;
}

void	get_heredoc(t_token *token, char **arg)
{
	int	i;
	int	nbh;

	i = 0;
	nbh = 0;
	while (arg[i] != 0)
	{
		if (ft_strcmp("<<", arg[i]) == 0)
			nbh++;
		i++;
	}
	if (nbh == 0)
		return ;
	token->delimiter = malloc(sizeof(char *) * (nbh + 1));
	if (!token->delimiter)
		return ;
	put_heredoc(token, arg);
}

void	get_append(t_token *token, char **arg, int i)
{
	int	fd;

	if (token->outfile == -1)
		return ;
	arg[i] = ft_remove_quote(arg[i]);
	fd = open(ft_remove_quote(arg[i]), O_APPEND | O_CREAT | O_RDWR, 0000644);
	if (access(arg[i], W_OK) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg[i], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		token->outfile = -1;
		g_exit_status = 1;
	}
	else
		token->outfile = fd;
	token->append = 1;
	if (i - 1 == token->last_o)
	{
		return ;
	}
	close(fd);
}

int	redirection(t_token *token, char **arg)
{
	int	i;

	i = 0;
	token->append = 0;
	token->outfile = 0;
	token->infile = 0;
	token->delimiter = NULL;
	get_heredoc(token, arg);
	token->last_o = nb_outfile(token, arg);
	token->last_i = nb_infile(token, arg);
	while (arg[i] != 0 && token->outfile != -1 && token->infile != -1)
	{
		if (ft_strcmp(">", arg[i]) == 0)
			get_outfile(token, arg, i + 1);
		else if (ft_strcmp("<", arg[i]) == 0)
			get_infile(token, arg, i + 1);
		else if (ft_strcmp(">>", arg[i]) == 0)
			get_append(token, arg, i + 1);
		i++;
	}
	return (1);
}
