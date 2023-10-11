/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:07:13 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 14:44:45 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	c;
	size_t	t;

	i = 0;
	c = 0;
	t = ft_strlen(to_find);
	if (to_find[0] == 0)
		return ((char *)str);
	if (str == to_find)
		return ((char *)str);
	while (str[i] != '\0' && (i + t) <= len)
	{
		c = 0;
		if (str[i] == to_find[c])
		{
			while (str[i + c] == to_find[c] && to_find[c] != '\0')
				c++;
			c--;
			if (str[i + c] != to_find[c])
				return (NULL);
			if (to_find[c + 1] == 0)
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}

