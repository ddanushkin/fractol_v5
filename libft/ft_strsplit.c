/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:25:50 by dgorold-          #+#    #+#             */
/*   Updated: 2019/02/28 13:09:27 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static size_t	cnt_words(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
		{
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static char		**del_array(char **array, size_t i)
{
	while (i > 0)
	{
		ft_strdel(&array[i]);
		i--;
	}
	free(array);
	return (NULL);
}

static char		**create_array(char *str, char c, char **array)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		len = 0;
		while (*str != '\0' && *str != c)
		{
			len++;
			str++;
		}
		array[i] = ft_strnew(len);
		if (array[i] == NULL)
			return (del_array(array, i));
		i++;
		if (*str == '\0')
			break ;
		str++;
	}
	return (array);
}

static char		**input_data(char **array, char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (*str)
	{
		if (*str != c)
		{
			j = 0;
			while (*str != c && *str != '\0')
			{
				array[i][j] = *str;
				str++;
				j++;
			}
			i++;
		}
		else
			str++;
	}
	array[i] = NULL;
	return (array);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	cnt;
	char	**array;
	char	*str;

	if (s != NULL && *s != '\0' && c != '\0')
	{
		cnt = cnt_words(s, c);
		str = (char*)s;
		array = (char**)malloc(sizeof(char*) * cnt + 1);
		if (array != NULL)
		{
			array = create_array(str, c, array);
			return (input_data(array, str, c));
		}
	}
	return (NULL);
}
