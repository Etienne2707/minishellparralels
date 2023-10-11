/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:36:32 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 17:28:02 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	charset_verif(char c, char d)
{
	if (c == d)
		return 1;
	return 0;
}

int	wordcount(char *str, char d)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && charset_verif(str[i], d) == 1)
			i++;
		if (str[i] != '\0' && charset_verif(str[i], d) == 0)
			c++;
		while (str[i] != '\0' && charset_verif(str[i], d) == 0)
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
		while (str[i] != '\0' && charset_verif(str[i], c) == 1)
			i++;
		while (str[i] != '\0' && charset_verif(str[i], c) == 0)
		{
			i++;
			k++;
		}
		if (k != 0)
		{
			dest[j] = malloc (sizeof(char) * (k + 1));
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
		while (str[i] != '\0' && charset_verif(str[i], c) == 1)
			i++;
		k = 0;
		while (str[i] != '\0' && charset_verif(str[i], c) == 0)
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
	char *str;
	
	str = (char *)s;
	if (str == 0 && str[0] == '\0')
		return (NULL);
	dest = malloc(sizeof(char *) * wordcount(str,c));
	if (!dest)
		return (NULL);
	makelengthmalloc(str, dest, c);
	wordinput(str, dest, c);
	return (dest);
}
