/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:46:01 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	size_t	size;
	size_t	i;

	i = 0;
	if (s && f)
	{
		size = ft_strlen(s);
		ptr = ft_strnew(size);
		if (ptr != NULL)
		{
			while (s[i])
			{
				ptr[i] = f(s[i]);
				i++;
			}
			return (ptr);
		}
	}
	return (NULL);
}
