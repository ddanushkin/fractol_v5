/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:10:16 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static char	*ft_create_new(char const *s, size_t l, size_t i)
{
	size_t	j;
	char	*new_str;

	j = 0;
	new_str = ft_strnew(l);
	if (new_str != NULL)
	{
		while (l-- > 0)
		{
			new_str[j] = (char)s[i + j];
			j++;
		}
		return (new_str);
	}
	return (NULL);
}

char		*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	l;

	i = 0;
	if (s)
	{
		l = ft_strlen(s) - 1;
		while (s[i] == '\n' || s[i] == ' ' || s[i] == '\t')
			i++;
		if (i == l + 1)
			return (ft_strnew(0));
		while (s[l] == '\n' || s[l] == ' ' || s[l] == '\t')
			l--;
		l = l - i + 1;
		return (ft_create_new(s, l, i));
	}
	return (NULL);
}
