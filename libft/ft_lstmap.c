/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:53:29 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static void	ft_delete_lst(t_list *list)
{
	t_list	*next;

	if (!list)
		return ;
	next = list->next;
	free(list->next);
	list->content = NULL;
	free(list);
	ft_delete_lst(next);
}

static void	ft_clear_list(t_list **head)
{
	ft_delete_lst(*head);
	*head = NULL;
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_dst;
	t_list	*lst_dst_ptr;

	if (lst == NULL || f == NULL)
		return (NULL);
	lst_dst = f(lst);
	if (lst_dst == NULL)
		return (NULL);
	lst_dst_ptr = lst_dst;
	while (lst->next)
	{
		lst = lst->next;
		lst_dst_ptr->next = f(lst);
		if (lst_dst_ptr->next == NULL)
		{
			ft_clear_list(&lst_dst_ptr);
			return (NULL);
		}
		lst_dst_ptr = lst_dst_ptr->next;
	}
	lst_dst_ptr->next = NULL;
	return (lst_dst);
}
