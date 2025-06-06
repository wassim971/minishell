/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:27:12 by wbaali            #+#    #+#             */
/*   Updated: 2024/11/18 10:27:17 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*current;
	t_list	*new_node;

	if (!lst || !f || !del)
		return (NULL);
	start = ft_lstnew(f(lst->content));
	if (!start)
		return (NULL);
	current = start;
	lst = lst->next;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (!new_node)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		current->next = new_node;
		current = new_node;
		lst = lst->next;
	}
	return (start);
}
