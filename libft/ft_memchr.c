/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:48:14 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/09 17:05:54 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int		i;
	unsigned char		c_cpy;
	unsigned char		*s_cpy;

	i = 0;
	c_cpy = (unsigned char) c;
	s_cpy = (unsigned char *)s;
	while (n)
	{
		if (s_cpy[i] == c_cpy)
			return ((void *) &s_cpy[i]);
		i++;
		n--;
	}
	return ((void *) 0x0);
}
