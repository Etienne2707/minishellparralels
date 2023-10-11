/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:21:27 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 14:17:42 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

int	ft_strlen2(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_strrchr(const char *str, int c)
{
	int i;

	i = 0;
	if (c == 0)
		return ((char *)(str + ft_strlen2((char *)str)));
	while (str[i] != '\0')
		i++;
	while ( i != 0)
	{
		if (((unsigned char *)str)[i] == (unsigned char)c)
			return ((char *)str + i);
		i--;
	}
	if (((unsigned char *)str)[0] == (unsigned char)c)
		return ((char *)str);
	return (NULL);
}