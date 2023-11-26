/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:01:45 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/26 11:07:06 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write1(int fd, char **str, int *pipefd, int i)
{
	(void)i;
	(void)pipefd;
	write(fd, *str, ft_strlen(*str));
	write(fd, "\n", 1);
	free(*str);
	*str = readline("> ");
}

static void	manage_files(int fd, t_pars *pars, char *str)
{
	if (fd)
		close(fd);
	if (!pars->infile)
		pars->infile = open(str, O_RDONLY);
}

static void	handle_ctrl_d_heredoc(t_pars *pars, int j)
{
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(pars->delimiter[j], 2);
	ft_putstr_fd("')\n", 2);
}

void	heredoc_loop(t_pars *pars, int *pipefd, int i, char *str)
{
	char	*line;
	int		fd;
	int		j;
	int		stdin_save;

	j = -1;
	fd = 0;
	stdin_save = dup(STDIN_FILENO);
	while (pars->delimiter[++j] != NULL)
	{
		fd = open_heredoc_file(str);
		line = readline("> ");
		while (line && (ft_strncmp(line, pars->delimiter[j],
					ft_strlen(pars->delimiter[j]) + 1)))
			write1(fd, &line, pipefd, i);
		if (!line && dup(0) != -1)
			handle_ctrl_d_heredoc(pars, j);
		free(line);
		manage_files(fd, pars, str);
		dup2(stdin_save, STDIN_FILENO);
	}
	close(stdin_save);
	free(str);
}
