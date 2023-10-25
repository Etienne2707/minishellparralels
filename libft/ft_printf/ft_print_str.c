/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:57:31 by mle-duc           #+#    #+#             */
/*   Updated: 2023/01/30 21:09:40 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_str(char *str, int *length)
{
	if (str == NULL)
	{
		ft_putstr("(null)");
		*length = *length + 6;
		return ;
	}
	ft_putstr(str);
	*length += ft_strlen(str);
}
