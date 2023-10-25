/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 20:42:49 by mle-duc           #+#    #+#             */
/*   Updated: 2023/02/24 16:32:55 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_hexa(unsigned int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

void	ft_put_hexa(unsigned int n, const char specifier)
{
	if (n >= 16)
	{
		ft_put_hexa(n / 16, specifier);
		ft_put_hexa(n % 16, specifier);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
		{
			if (specifier == 'x')
				ft_putchar(n + 'a' - 10);
			else if (specifier == 'X')
				ft_putchar(n + 'A' - 10);
		}
	}
}

void	ft_print_hexa(unsigned int n, const char specifier, int *length)
{
	if (n == 0)
		*length += write(1, "0", 1);
	else
	{
		ft_put_hexa(n, specifier);
		*length += ft_len_hexa(n);
	}
}
