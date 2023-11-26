/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:12:18 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/26 20:13:12 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separator_in_quotes(char *str, int i)
{
	if (str[i] == 32)
		return (check_in_quote(str, i));
	else if (str[i] == '|')
		return (check_in_quote(str, i));
	else
		return (1);
}

int	d_hd(char *str, int i)
{
	int	k;
	int	index;

	k = 0;
	if (str[i] != '$')
		return (0);
	while (str[k] != '\0')
	{
		if (str[k] == '<' && str[k + 1] == '<')
		{
			index = k;
			k += 2;
			while (str[k] == 32 && str[k] != '\0')
				k++;
			while (str[k] != '\0' && separator_in_quotes(str, k) != -1)
				k++;
			if (i > index && i < k)
				return (-1);
		}
		k++;
	}
	return (1);
}
