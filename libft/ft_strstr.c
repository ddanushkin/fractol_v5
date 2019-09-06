/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:49:19 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		val;

	val = 0;
	i = -1;
	if (!*needle)
		return ((char*)haystack);
	while (haystack[++i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			val = i;
			while (haystack[i] == needle[j] && needle[j])
			{
				i++;
				j++;
			}
			if (needle[j] == '\0')
				return (((char*)haystack + val));
			i = val;
		}
	}
	return (NULL);
}
