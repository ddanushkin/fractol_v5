/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 13:50:36 by dgorold-          #+#    #+#             */
/*   Updated: 2019/01/10 19:06:04 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;

	i = 0;
	if (s1 && s2)
	{
		new_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (new_str != NULL)
		{
			while (s1[i])
			{
				new_str[i] = (char)s1[i];
				i++;
			}
			while (*s2)
			{
				new_str[i] = (char)*s2;
				i++;
				s2++;
			}
			return (new_str);
		}
	}
	return (NULL);
}
