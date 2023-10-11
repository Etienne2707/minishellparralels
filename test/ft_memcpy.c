/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:53:20 by educlos           #+#    #+#             */
/*   Updated: 2022/11/14 11:40:12 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	char *temp;
	char *temp2;
	size_t i;
	temp = (char *)dest;
	temp2 = (char *)src;

	i = 0;
	while (i < n)
	{
		temp[i] = temp2[i];
		i++;
	}
	return (dest);
}
