/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:01 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/12 15:05:51 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*ret;

	if (size && (size * nmemb) / (size) != nmemb)
		return (0);
	ret = malloc (nmemb * size);
	if (!ret)
		return (0);
	ft_bzero(ret, nmemb * size);
	return (ret);
}
