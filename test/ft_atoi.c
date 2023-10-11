/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 16:59:37 by educlos           #+#    #+#             */
/*   Updated: 2022/11/14 17:45:47 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int result;
	char *str2;

	i = 0;
	sign = 1;
	result = 0;
	str2 = (char *)str;
	while ((str2[i] >= 9 && str2[i] <= 13 )|| str2[i] == 32)
		i++;
	if (str2[i] == '+')
		i++;
	else if (str2[i] == '-')
	{
		i++;
		sign = sign * - 1;
	}
	while (str2[i] >= '0' && str2[i] <= '9' && str2[i] != '\0')
	{
		result *= 10;
		result = result + str2[i] - '0';
		i++;
	}
	return (result * sign);
}
