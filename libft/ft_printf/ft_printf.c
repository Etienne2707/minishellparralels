/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:16:07 by mle-duc           #+#    #+#             */
/*   Updated: 2023/02/24 16:32:26 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_specifier(va_list ap, const char specifier, int *length)
{
	if (specifier == 'c')
		ft_print_char(va_arg(ap, int), length);
	else if (specifier == 's')
		ft_print_str(va_arg(ap, char *), length);
	else if (specifier == 'p')
		ft_print_ptr(va_arg(ap, unsigned long long), length);
	else if (specifier == 'd' || specifier == 'i')
		ft_print_nb(va_arg(ap, int), length);
	else if (specifier == 'u')
		ft_print_unsigned(va_arg(ap, unsigned int), length);
	else if (specifier == 'x' || specifier == 'X')
		ft_print_hexa(va_arg(ap, unsigned int), specifier, length);
	else if (specifier == '%')
		ft_print_percent(length);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		length;
	int		*length_ptr;

	i = 0;
	length = 0;
	length_ptr = &length;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			ft_specifier(ap, str[i + 1], length_ptr);
			i++;
		}
		else
		{
			*length_ptr = *length_ptr + 1;
			ft_putchar(str[i]);
		}
		i++;
	}
	va_end(ap);
	return (length);
}
