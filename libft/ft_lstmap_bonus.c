/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-duc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:30 by mle-duc           #+#    #+#             */
/*   Updated: 2022/11/11 14:11:13 by mle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*retlist;
	t_list	*temp;

	retlist = malloc(sizeof(t_list));
	if (!lst || !del || !f || !retlist)
		return (0);
	retlist->content = f(lst->content);
	retlist->next = NULL;
	lst = lst->next;
	while (lst != NULL)
	{
		temp = ft_lstnew(f(lst->content));
		if (!temp)
		{
			ft_lstclear(&retlist, del);
			break ;
		}
		ft_lstadd_back(&retlist, temp);
		lst = lst->next;
	}
	return (retlist);
}
