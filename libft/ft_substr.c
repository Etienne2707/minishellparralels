/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 19:44:47 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/14 19:48:03 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getsize(char const *s, unsigned int start, size_t len)
{
	size_t	size;

	size = 0;
	while (size < len && start < (unsigned int)ft_strlen(s) && s[size + start])
		size++;
	return (size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	size;

	if (!s)
		return (0);
	size = getsize(s, start, len);
	ret = malloc (sizeof(char) *(size + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < len && start < (unsigned int)ft_strlen(s) && s[i + start])
	{
		ret[i] = s[start + (unsigned int)i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
