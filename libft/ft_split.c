/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:06:53 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/13 10:54:58 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char *str, int len)
{
	int	count;
	int	i;
	int	boolean;

	count = 0;
	i = 0;
	boolean = 0;
	while (i < len)
	{
		if (str[i] && !boolean)
			count++;
		boolean = str[i];
		i++;
	}
	return (count);
}

static char	*ft_extract(const char *str, char c, char *res)
{
	int	i;

	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		if (str[i] == c)
			res[i] = 0;
		i++;
	}
	res[i] = 0;
	return (res);
}

static char	*ft_stralloc(char *src, char **ret)
{
	char	*dst;
	int		j;

	dst = ft_strdup(src);
	if (!dst)
	{
		j = 0;
		while (ret[j])
			free(ret[j++]);
		free(ret);
		return (0);
	}
	return (dst);
}

static char	**split(char *tmp, int words)
{
	int		boolean;
	char	**ret;
	int		i;

	boolean = 0;
	i = 0;
	ret = ft_calloc(words + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	while (i < words)
	{
		if (*tmp && !boolean)
		{
			ret[i] = ft_stralloc(tmp, ret);
			if (!(ret[i++]))
				return (NULL);
		}
		boolean = *tmp;
		tmp++;
	}
	ret[i] = 0;
	return (ret);
}

char	**ft_split(char const *str, char c)
{
	char	*res;
	int		nb_words;
	char	**ret;

	if (!str)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!res)
		return (NULL);
	nb_words = ft_count_words(ft_extract(str, c, res), ft_strlen(str));
	ret = split(ft_extract(str, c, res), nb_words);
	if (res)
		free(res);
	return (ret);
}
