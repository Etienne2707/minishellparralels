/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:30:41 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 17:16:13 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t ft_strlen(char const *str)
{
    int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}



char *ft_substr(char const *s, unsigned int start,size_t len)
{
	char *s2;
	size_t i;

	i = 0;
	if (!s)
		return NULL;
	if (start >= ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	s2 = malloc (sizeof(char) * len + 1);
	if (!s2)
		return NULL;
	while (s[i] && i < len)
	{
		s2[i] = s[i + start];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}