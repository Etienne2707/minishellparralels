/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:10 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/07 14:01:10 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*temp2;

	if (!lst || !del)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		temp2 = temp;
		temp = temp->next;
		ft_lstdelone(temp2, del);
	}
	*lst = NULL;
}
