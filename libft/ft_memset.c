/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:11:38 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/01 18:13:02 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{	
	unsigned char	*a;

	a = b;
	while (len--)
	{
		*a++ = (unsigned char) c;
	}
	return (b);
}
