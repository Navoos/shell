/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:21:04 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/09 16:59:53 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dist, const void *src, size_t n)
{
	char		*a;
	const char	*b;

	if (dist == NULL && src == NULL)
		return (NULL);
	a = (char *) dist;
	b = (const char *) src;
	while (n--)
	{
		*a = *b;
		a++;
		b++;
	}
	return (dist);
}
