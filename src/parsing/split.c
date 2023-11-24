/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:17:23 by educlos           #+#    #+#             */
/*   Updated: 2023/11/24 12:04:43 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	charset_verif(char *str, char c, char d, int i)
{
	if (c == d)
	{
		if (check_in_quote(str, i) != 1)
		{
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	wordcount(char *str, char d)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (charset_verif(str, str[i], d, i) == 1))
			i++;
		if (str[i] != '\0' && charset_verif(str, str[i], d, i) == 0)
			c++;
		while (str[i] != '\0' && charset_verif(str, str[i], d, i) == 0)
			i++;
	}
	return (c + 1);
}

void	makelengthmalloc(char *str, char **dest, char c)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] != '\0' && charset_verif(str, str[i], c, i) == 1)
			i++;
		while (str[i] != '\0' && charset_verif(str, str[i], c, i) == 0)
		{
			i++;
			k++;
		}
		if (k != 0)
		{
			dest[j] = malloc(sizeof(char) * (k + 1));
			if (!dest[j])
				return ;
		}
		j++;
	}
}

void	wordinput(char *str, char **dest, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && charset_verif(str, str[i], c, i) == 1)
			i++;
		k = 0;
		while (str[i] != '\0' && charset_verif(str, str[i], c, i) == 0)
		{
			dest[j][k] = str[i];
			i++;
			k++;
		}
		if (k != 0)
		{
			dest[j][k] = '\0';
			j++;
		}
	}
	dest[j] = 0;
}

char	**ft_split(const char *s, char c)
{
	char	**dest;
	char	*str;

	str = (char *)s;
	if (str == 0 || str[0] == '\0')
		return (NULL);
	dest = malloc(sizeof(char *) * wordcount(str, c));
	if (!dest)
		return (NULL);
	makelengthmalloc(str, dest, c);
	wordinput(str, dest, c);
	return (dest);
}
