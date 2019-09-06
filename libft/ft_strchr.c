/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:07:04 by dgorold-          #+#    #+#             */
/*   Updated: 2019/01/14 15:22:24 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	if (s == NULL || c == 0)
		return (NULL);
	i = 0;
	ptr = (char*)s;
	while (s[i])
	{
		if ((int)s[i] == c)
		{
			return ((ptr + i));
		}
		i++;
	}
	if (c == '\0')
	{
		return (ptr + i);
	}
	return (NULL);
}
