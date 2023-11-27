/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 06:52:55 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/27 07:27:44 by mle-duc          ###   ########.fr       */
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

int	only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 32 && (str[i] < 9 || str[i] > 13))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_dollars2(char *str, char **envp, char *dest)
{
	char	*temp;
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		if (is_solo_dol(str, i) != 0 && dollars_in_quote(str, i) == 1
			&& d_hd(str, i) == 1)
		{
			temp = swap_value(get_value(str, i), envp);
			if (temp != NULL)
				dest = change_value(temp, dest);
			else
			{
				dest = remove_dol(dest, get_value(str, i));
				if (dest[0] == 0 || (only_space(dest) == 1))
				{
					free(dest);
					return (NULL);
				}
			}
		}
		i++;
	}
	return (dest);
}
