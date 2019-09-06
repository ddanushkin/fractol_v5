/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:14:48 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*pos;
	size_t	len;

	pos = ft_memchr(src, c, n);
	if (pos == NULL)
	{
		ft_memcpy(dst, src, n);
		return (NULL);
	}
	len = pos - src + 1;
	ft_memcpy(dst, src, len);
	return (ft_memchr(dst, c, n) + 1);
}
