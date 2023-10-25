/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:49:32 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/18 16:56:43 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*chars_before_nl(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != 0)
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (0);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	line[j] = 0;
	return (line);
}

char	*chars_after_nl(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[j])
		j++;
	while (buffer[i] != '\n' && buffer[i] != 0)
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (j - i + 1));
	if (!line)
		return (0);
	j = 0;
	while (buffer[i + j])
	{
		line[j] = buffer[i + j];
		j++;
	}
	line[j] = 0;
	return (line);
}

void	read_fd(int fd, char **memorized, char **leftover)
{
	char	*buffer;
	int		reader;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return ;
	reader = read(fd, buffer, BUFFER_SIZE);
	while (reader > 0)
	{
		buffer[reader] = 0;
		*leftover = ft_strdup(*memorized);
		reset(memorized);
		*memorized = ft_realloc(*leftover, buffer);
		if (find_nl(*memorized))
			break ;
		reader = read(fd, buffer, BUFFER_SIZE);
	}
	if (reader < 0)
	{
		free(buffer);
		reset(leftover);
		reset(memorized);
		return ;
	}
	free(buffer);
}

char	*ft_line(char **memorized)
{
	char	*line;
	char	*temp;

	temp = ft_strdup(*memorized);
	reset(memorized);
	if (!find_nl(temp))
	{
		line = ft_strdup(temp);
		if (temp)
			free(temp);
		return (line);
	}
	*memorized = chars_after_nl(temp);
	line = chars_before_nl(temp);
	reset(&temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*memorized = NULL;
	char		*line;
	char		*leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = NULL;
	leftover = NULL;
	read_fd(fd, &memorized, &leftover);
	if (memorized && *memorized)
		line = ft_line(&memorized);
	if (!line || !(*line))
	{
		reset(&memorized);
		free(line);
		return (0);
	}
	return (line);
}
