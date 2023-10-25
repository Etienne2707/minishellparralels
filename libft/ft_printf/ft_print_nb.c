/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 21:16:02 by mle-duc           #+#    #+#             */
/*   Updated: 2023/01/30 21:18:16 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_nb(int n, int *length)
{
	char	*str;

	str = ft_itoa(n);
	ft_putstr(str);
	*length += ft_strlen(str);
	free(str);
}
