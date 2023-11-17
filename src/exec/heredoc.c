/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:01:45 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/17 13:43:58 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write1(int fd, char **str, int *pipefd, int i)
{
	if (i == 0)
	{
		write(fd, *str, ft_strlen(*str));
		write(fd, "\n", 1);
	}
	else
	{
		write(pipefd[2 * (i - 1) + 1], *str, ft_strlen(*str));
		write(pipefd[2 * (i - 1) + 1], "\n", 1);
	}
	free(*str);
	*str = readline("> ");
}

void	ft_heredoc(t_pars *pars, int *pipefd, int i)
{
	int		len;
	char	*line;
	int		j;
	int		fd;

	j = -1;
	fd = 0;
	while (pars->delimiter[++j] != NULL)
	{
		line = readline("> ");
		len = ft_strlen(pars->delimiter[j]);
		if (i == 0)
		{
			fd = open (".heredoc_tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd < 0)
				exit(EXIT_FAILURE);
		}
		while (line && (ft_strncmp(line, pars->delimiter[j], len)))
			write1(fd, &line, pipefd, i);
		free(line);
		if (fd)
			close(fd);
	if (!pars->infile && i == 0)
		pars->infile = open(".heredoc_tmp", O_RDONLY);
	}
}
