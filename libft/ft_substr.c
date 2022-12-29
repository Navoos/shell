/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:01:49 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/12 16:16:26 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;

	i = 0;
	if (!s)
		return (0x0);
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *) malloc(sizeof(char) * len + 1);
	if (!ptr)
		return ((char *)0x0);
	if (start < ft_strlen(s))
	{
		while (i < len)
		{
			ptr[i] = s[start + i];
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}
