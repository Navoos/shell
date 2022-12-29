/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:54:43 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/12 15:22:37 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize >= 1)
	{
		while (i + 1 < dstsize && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		if (i < dstsize)
			dst[i] = 0;
	}
	return (ft_strlen(src));
}
