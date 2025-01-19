/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juaho <juaho@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:28:30 by juaho             #+#    #+#             */
/*   Updated: 2024/11/21 18:43:38 by juaho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_node;
	void	*f_ret;

	if (!f || !del || !lst)
		return (NULL);
	new_head = NULL;
	while (lst)
	{
		f_ret = f(lst->content);
		new_node = ft_lstnew(f_ret);
		if (!new_node)
		{
			ft_lstclear(&new_head, del);
			del(f_ret);
			return (NULL);
		}
		ft_lstadd_back(&new_head, new_node);
		lst = lst->next;
	}
	return (new_head);
}
