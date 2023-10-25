/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:46 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/12 15:50:41 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long nb)
{
	int	len;

	if (nb == 0)
		return (1);
	len = 0;
	if (nb < 0)
	{
			nb *= -1;
			len++;
	}
	while (nb > 0)
	{
			nb /= 10;
			len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		i;

	nb = n;
	i = len(nb);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (0);
	str[i--] = '\0';
	if (nb == 0)
			str[0] = 48;
	if (nb < 0)
	{
			str[0] = '-';
			nb *= -1;
	}
	while (nb > 0)
	{
			str[i] = '0' + (nb % 10);
			nb /= 10;
			i--;
	}
	return (str);
}
