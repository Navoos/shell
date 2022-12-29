/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:05:03 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/09 19:50:55 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static void	ft_convert(int n, char *tmp, int *index)
{
	long	t;

	t = (long) n;
	if (t < 0)
	{
		t = -t;
		tmp[++(*index)] = '-';
	}
	if (t >= 10)
	{
		ft_convert(t / 10, tmp, index);
		t = t % 10;
	}
	if (t < 10)
	{
		tmp[++(*index)] = t + 48;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	tmp[13];
	int		*index_ptr;
	int		index;

	index = -1;
	index_ptr = &index;
	ft_convert(n, tmp, index_ptr);
	tmp[index + 1] = 0;
	ft_putstr_fd(tmp, fd);
}
