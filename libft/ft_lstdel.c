/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:59:31 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp;

	if (alst != NULL && *alst != NULL && (*alst)->content != NULL)
	{
		while ((*alst))
		{
			tmp = (*alst)->next;
			ft_lstdelone(&(*alst), del);
			(*alst) = tmp;
		}
		free(*alst);
		*alst = NULL;
	}
}
