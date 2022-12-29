/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:41:04 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/09 18:18:30 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;
	size_t	c;

	i = 0;
	c = 0;
	len_needle = ft_strlen(needle);
	if (!*needle || haystack == needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		c = 0;
		while (haystack[i + c] && needle[c]
			&& haystack[i + c] == needle[c] && i + c < len)
		{
			c++;
		}
		if (c == len_needle)
			return ((char *) haystack + i);
		i++;
	}
	return ((char *) 0x0);
}
