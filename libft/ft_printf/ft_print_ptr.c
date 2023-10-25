/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:04:32 by mle-duc           #+#    #+#             */
/*   Updated: 2023/01/30 21:36:41 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_len(uintptr_t n)
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

void	ft_put_ptr(uintptr_t n)
{
	if (n >= 16)
	{
		ft_put_ptr(n / 16);
		ft_put_ptr(n % 16);
	}
	else
	{
		if (n <= 9)
			ft_putchar(n + '0');
		else
			ft_putchar(n + 'a' - 10);
	}
}

void	ft_print_ptr(unsigned long long ptr, int *length)
{
	if (ptr == 0)
		*length += write(1, "(nil)", 5);
	else
	{
		*length += write(1, "0x", 2);
		ft_put_ptr(ptr);
		*length = *length + ft_ptr_len(ptr);
	}
}
