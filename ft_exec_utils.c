/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 13:23:49 by mzridi            #+#    #+#             */
/*   Updated: 2022/12/31 13:23:55 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static unsigned int	ft_skip(char *s, char c, unsigned int i, int type)
{
	if (type == 1)
	{
		if (c == 0)
			return (i);
		while (s[i] == c)
				i++;
		return (i);
	}
	else
	{
		while (s[i] != c && s[i] != 0)
				i++;
		return (i);
	}
}

unsigned int	ft_wcount(char *s, char c)
{
	unsigned int	i;
	unsigned int	result;

	i = 0;
	result = 0;
	i = ft_skip(s, c, i, 1);
	while (s[i] != 0)
	{
		result += 1;
		i = ft_skip(s, c, i, 0);
		i = ft_skip(s, c, i, 1);
	}
	return (result);
}
