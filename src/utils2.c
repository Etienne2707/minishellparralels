/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:12:59 by educlos           #+#    #+#             */
/*   Updated: 2023/10/25 18:38:01 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_compare(char *str, char *str2, int size)
{
	int	i;

	i = 0;
	if (!str)
	{
		return (-1);
	}
	while (str[i] == str2[i] && i < size - 1 && str2[i] != '\0'
		&& str[i] != '\0')
		i++;
	if (str2[i + 1] != '=')
		return (-1);
	else
		return (str[i] - str2[i]);
}

char	*ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	l;

	i = 0;
	l = ft_strlen(src);
	while (size != 0 && i < size - 1 && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	str = malloc(sizeof(char) * i + k + 1);
	if (!str)
		return (NULL);
	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		str[i] = s2[k];
		i++;
		k++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strnjoin(char *s1, char *s2, int c)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = ft_strlen(s1);
	k = ft_strlen(s2) - c;
	str = malloc(sizeof(char) * i + k + 1);
	if (!str)
		return (NULL);
	i = 0;
	k = c;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		str[i] = s2[k];
		i++;
		k++;
	}
	str[i] = 0;
	return (str);
}

char	*add_space_2(char *st, char *dest)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (st[i] != '\0')
	{
		if ((st[i] == '<' || st[i] == '>') && (check_in_quote(st, i) == -1))
		{
			dest[c++] = 32;
			while (st[i] == '<' ||(st[i] == '>' && st[i] != '\0'))
				dest[c++] = st[i++];
			dest[c++] = 32;
		}
		dest[c++] = st[i++];
	}
	dest[c] = '\0';
	return (dest);
}

char	*add_space(char *st)
{
	int		i;
	int		c;
	char	*dest;

	i = 0;
	c = 0;
	if (!st)
		return (NULL);
	while (st[i])
	{
		if ((st[i] == '>' || st[i] == '<') && (check_in_quote(st, i) == -1))
		{
			i++;
			c++;
		}
		if (st[i] == '>' || st[i] == '<')
			i++;
		i++;
	}
	dest = malloc(sizeof(char) * ft_strlen(st) + (c * 2) + 1);
	if (!dest)
		return (NULL);
	dest = add_space_2(st, dest);
	free(st);
	return (dest);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}