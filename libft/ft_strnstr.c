/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:03:20 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/11 16:54:58 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	int		boolean;

	if (!(*little))
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		j = 0;
		boolean = 1;
		while (little[j] && boolean)
		{
			if ((i + j) <= len && little[j] != big[i + j])
				boolean = 0;
			j++;
		}
		if (i + j <= len && boolean)
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
