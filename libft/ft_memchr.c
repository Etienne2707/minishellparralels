/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:48 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/07 14:01:48 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*c1;
	size_t			i;

	i = 0;
	c1 = (unsigned char *)s;
	while (i < n)
	{
		if (c1[i] == (unsigned char)c)
			return (c1 + i);
		i++;
	}
	return (0);
}
