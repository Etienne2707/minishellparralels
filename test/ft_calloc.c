/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:11:53 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 17:38:13 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t total;
	char *mem;
	size_t i;
	if (count && (count * size) / count != size)
		return (NULL);
	total = count * size;
	mem = malloc(total);
	
	if (mem == NULL || (count * size) / count != size)
		return (NULL);
	i = 0;
	while (i < total)
	{
		mem[i] = 0;
		i++;		
	}
	return (mem);
}


