/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:56 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/07 14:01:57 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	if (!dest && !src)
		return (dest);
	i = -1;
	c1 = (unsigned char *)src;
	c2 = (unsigned char *)dest;
	while (++i < n)
		c2[i] = c1[i];
	return (dest);
}
