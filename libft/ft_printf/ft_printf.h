/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:54:30 by mle-duc           #+#    #+#             */
/*   Updated: 2023/04/09 03:08:59 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include "../libft.h"

int		ft_printf(const char *str, ...);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_print_char(char c, int *length);
void	ft_print_str(char *str, int *length);
void	ft_print_ptr(unsigned long long ptr, int *length);
void	ft_print_unsigned(unsigned int n, int *length);
void	ft_print_hexa(unsigned int n, const char specifier, int *length);
void	ft_print_percent(int *length);
void	ft_print_nb(int n, int *length);

#endif
