/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:37:37 by educlos           #+#    #+#             */
/*   Updated: 2022/11/14 17:10:12 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int ft_memcmp( const void * p1, const void * p2, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		if (((unsigned char *)p1)[i] != ((unsigned char *)p2)[i])
			return (((unsigned char *)p1)[i] - ((unsigned char *)p2)[i]);
		i++;
	}
	return (0);
}