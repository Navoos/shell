/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:24:27 by yakhoudr          #+#    #+#             */
/*   Updated: 2021/11/02 18:40:12 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char			to_find;
	unsigned int	i;

	to_find = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == to_find)
			return ((char *)(&s[i]));
		i++;
	}
	if (to_find == '\0')
		return ((char *)(&s[i]));
	return ((char *)0x0);
}
