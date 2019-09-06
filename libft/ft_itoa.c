/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:26:57 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static	size_t	len_of_nbr(long long n)
{
	size_t		len;

	len = 0;
	if (n < 0)
	{
		len = 1;
		n = n * -1;
	}
	if (n != 0)
	{
		while (n >= 10)
		{
			n = n / 10;
			len++;
		}
		return (len + 1);
	}
	return (1);
}

static char		*create_array(long long n, size_t len, char *str, int sign)
{
	while (n >= 10)
	{
		str[len] = n % 10 + '0';
		len--;
		n = n / 10;
	}
	str[len] = n % 10 + '0';
	if (sign < 0)
	{
		len--;
		str[len] = '-';
	}
	return (str);
}

char			*ft_itoa(int n)
{
	size_t		len;
	char		*str;
	int			sign;
	long long	nbr;

	nbr = n;
	sign = 1;
	if (nbr < 0)
		sign = -1;
	len = len_of_nbr(nbr);
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	return (create_array(nbr * sign, --len, str, sign));
}
