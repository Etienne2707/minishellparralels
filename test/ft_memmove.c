/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:07:12 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 17:56:48 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void *ft_memmove(void *dest, const void *src, size_t n)
{
	char *temp;
	char *temp2;
	char temp3;
	size_t i;
	temp = (char *)dest;
	temp2 = (char *)src;
	i = 0;
	while (i < n)
	{
		if (n != 0)
		{
			n--;
			temp[n] = temp2[n];
		}
		else
		{
			temp3 = temp2[i];
			temp[i] = temp3;
			i++;
		}
	}
	return (dest);
}
