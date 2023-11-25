/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 13:01:39 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/25 13:03:37 by mle-duc          ###   ########.fr       */
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
