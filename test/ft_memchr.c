/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:00:52 by educlos           #+#    #+#             */
/*   Updated: 2022/11/14 15:57:58 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void*	ft_memchr(const void* tab, int c, size_t s)
{
	size_t i;

	i = 0;
	while (i < s)
	{
	if (((unsigned char *)tab)[i] == (unsigned char)c)
		{
			return ((void *)(tab + i));
		}
		i++;
	}
	return (NULL);
}