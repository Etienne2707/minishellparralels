/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:32:14 by mle-duc           #+#    #+#             */
/*   Updated: 2023/02/24 16:32:40 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uintlen(unsigned int n)
{
	int	uintlen;

	uintlen = 0;
	while (n != 0)
	{
		uintlen++;
		n = n / 10;
	}
	return (uintlen);
}

char	*ft_utoa(unsigned int n)
{
	char	*str;
	int		len;

	len = ft_uintlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	while (n != 0)
	{
		str[len - 1] = '0' + (n % 10);
		n = n / 10;
		len = len - 1;
	}
	return (str);
}

void	ft_print_unsigned(unsigned int n, int *length)
{
	char	*str;

	if (n == 0)
		*length += write(1, "0", 1);
	else
	{
		str = ft_utoa(n);
		ft_putstr(str);
		*length += ft_strlen(str);
		free(str);
	}
}
