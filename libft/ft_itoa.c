/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 11:27:40 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/09 18:37:01 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_itoa(int n)
{
	char			tmp[13];
	int				index;
	int				*ptr;
	char			*out;

	index = -1;
	ptr = &index;
	ft_convert(n, tmp, ptr);
	out = (char *) malloc(*ptr + 2);
	if (!out)
		return ((char *) 0x0);
	ft_strlcpy(out, tmp, *ptr + 2);
	return (out);
}
