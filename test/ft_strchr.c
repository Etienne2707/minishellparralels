/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:44:46 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 14:13:02 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen2(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	if (c == 0)
		return ((char *)(str + ft_strlen2(str)));
	while (str[i] != '\0')
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}