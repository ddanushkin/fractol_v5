/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgorold- <dgorold-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:08:11 by dgorold-          #+#    #+#             */
/*   Updated: 2018/12/09 16:01:00 by dgorold-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	tmp1;
	unsigned char	tmp2;

	if ((unsigned char)c < 128)
		write(fd, &c, 1);
	else
	{
		tmp1 = 192 + (unsigned char)c / 64;
		tmp2 = 128 + (unsigned char)c % 64;
		write(fd, &tmp1, 1);
		write(fd, &tmp2, 1);
	}
}
