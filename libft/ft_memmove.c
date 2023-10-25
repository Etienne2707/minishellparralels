/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:02:00 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/07 14:02:01 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	if (!dest && !src)
		return (dest);
	i = 0;
	c1 = (unsigned char *)src;
	c2 = (unsigned char *)dest;
	if (c2 > c1)
	{
		i = n;
		while (i--)
			c2[i] = c1[i];
	}
	else if (c1 > c2)
	{
		i = -1;
		while (++i < n)
			c2[i] = c1[i];
	}
	return (dest);
}
