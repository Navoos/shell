/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:44:08 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/03 20:54:58 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	while (n--)
	{
		a = (unsigned char *) s1;
		b = (unsigned char *) s2;
		if (*a != *b)
			return (*a - *b);
		s1++;
		s2++;
	}
	return (0);
}
