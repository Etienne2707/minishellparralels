/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:01:45 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/25 19:48:43 by mle-duc          ###   ########.fr       */
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

static char	*tmpfile_name(int i)
{
	char	*index;
	char	*file_name;

	index = ft_itoa(i);
	if (!index)
		return (NULL);
	file_name = ft_strjoin(".heredoc_tmp_", index);
	free(index);
	return (file_name);
}

static void	manage_files(int fd, t_pars *pars, char *str)
{
	if (fd > 0)
		close(fd);
	if (!pars->infile)
		pars->infile = open(str, O_RDONLY);
}

void	handle_ctrl_d_heredoc(t_pars *pars, int j)
{
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(pars->delimiter[j], 2);
	ft_putstr_fd("')\n", 2);
}

void	ft_heredoc(t_pars *pars, int *pipefd, int i)
{
	int		len;
	char	*line;
	int		j;
	int		fd;
	char	*str;
	int	stdin_save;

	j = -1;
	fd = 0;
	str = tmpfile_name(i);
	signal(SIGINT, handle_sigint_heredoc);
	stdin_save = dup(STDIN_FILENO);
	while (pars->delimiter[++j] != NULL)
	{
		fd = open_heredoc_file(str);
		line = readline("> ");
		len = ft_strlen(pars->delimiter[j]);
		while (line && (ft_strncmp(line, pars->delimiter[j], len + 1)))
			write1(fd, &line, pipefd, i);
		if (!line && dup(0) != -1) 
			handle_ctrl_d_heredoc(pars, j);
		free(line);
		manage_files(fd, pars, str);
		dup2(stdin_save, STDIN_FILENO);
	}
	free(str);
}
