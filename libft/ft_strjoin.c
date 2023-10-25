/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:02:41 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/12 16:23:37 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	lens1;
	size_t	lens2;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	ret = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!ret)
		return (0);
	i = -1;
	while (++i < lens1)
		ret[i] = s1[i];
	i = -1;
	while (++i < lens2)
		ret[lens1 + i] = s2[i];
	ret[lens1 + i] = 0;
	return (ret);
}
