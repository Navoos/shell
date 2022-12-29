/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmemove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:57:11 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/08 21:46:11 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char *) dst;
	s = (char *) src;
	if (dst == src)
		return (dst);
	else if (dst > src)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
		ft_memcpy(d, src, len);
	return (dst);
}	
