/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:02:24 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 15:18:19 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	exit_value;

	if (!s)
		return (EXIT_FAILURE);
	exit_value = write(fd, s, ft_strlen(s));
	if (exit_value == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
