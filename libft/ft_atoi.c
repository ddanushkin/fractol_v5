/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:16:56 by dgorold-          #+#    #+#             */
/*   Updated: 2019/03/18 16:05:45 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

static int	ft_checking(unsigned long long nbr, int sign)
{
	if (nbr > 9223372036854775807)
		return ((sign > 0) ? -1 : 0);
	else
		return (sign * (int)nbr);
}

int			ft_atoi(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	res;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] && ((str[i] >= 0 && str[i] <= 42) || str[i] == 44))
	{
		if (str[i] == '\e')
			return (0);
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		(str[i] == '-') ? sign = -1 : sign;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (ft_checking(res, sign));
}
