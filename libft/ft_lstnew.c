/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 12:02:53 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (ptr != NULL)
	{
		ptr->next = NULL;
		if (content != NULL)
		{
			ptr->content = malloc(content_size);
			if (ptr->content != NULL)
			{
				ft_memcpy(ptr->content, content, content_size);
				ptr->content_size = content_size;
				return (ptr);
			}
			free(ptr);
			return (NULL);
		}
		ptr->content = NULL;
		ptr->content_size = 0;
		return (ptr);
	}
	return (NULL);
}
