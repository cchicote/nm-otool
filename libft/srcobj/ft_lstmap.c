/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 15:58:09 by cchicote          #+#    #+#             */
/*   Updated: 2015/12/07 15:58:11 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp1;
	t_list	*tmp2;

	if (!lst || !f)
		return (NULL);
	tmp2 = f(lst);
	if ((new = ft_lstnew(tmp2->content, tmp2->content_size)))
	{
		tmp1 = new;
		lst = lst->next;
		while (lst)
		{
			tmp2 = f(lst);
			if (!(tmp1->next = ft_lstnew(tmp2->content, tmp2->content_size)))
				return (NULL);
			tmp1 = tmp1->next;
			lst = lst->next;
		}
	}
	return (new);
}
