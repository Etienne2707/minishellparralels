/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <mle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 02:30:48 by mle-duc           #+#    #+#             */
/*   Updated: 2023/11/29 02:32:07 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*malloc_cpy(char *dest, char *src)
{
	if (!src || src[0] == 0)
		return (NULL);
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	dest = ft_strcpy(dest, src);
	dest[ft_strlen(src)] = '\0';
	return (dest);
}
