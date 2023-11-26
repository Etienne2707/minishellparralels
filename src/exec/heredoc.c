/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:01:39 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/26 11:02:07 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_heredoc_file(char *str)
{
	int	fd;

	fd = open (str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		free(str);
		exit(EXIT_FAILURE);
	}
	return (fd);
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

void	ft_heredoc(t_pars *pars, int *pipefd, int i)
{
	char	*str;

	str = tmpfile_name(i);
	signal(SIGINT, handle_sigint_heredoc);
	heredoc_loop(pars, pipefd, i, str);
}
