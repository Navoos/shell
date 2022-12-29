/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __find.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:38:21 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/09 21:52:08 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__key(char *env__, int i__)
{
	char	*key__;
	int		j__;

	key__ = 0x0;
	key__ = ft_collect_tmp_mem(malloc(sizeof(char) * (i__ + 1)));
	if (!key__)
		return (0x0);
	j__ = 0;
	while (j__ < i__ && env__[j__])
	{
		key__[j__] = env__[j__];
		j__ += 1;
	}
	key__[j__] = '\0';
	return (key__);
}

char	*__val(char *env__, int i__)
{
	char	*__val__;
	int		j__;

	__val__ = 0x0;
	__val__ = ft_collect_tmp_mem(malloc(sizeof(char)
				* (ft_strlen(env__) - i__)));
	if (!__val__)
		return (0x0);
	j__ = 0;
	while (env__[i__ + j__])
	{
		__val__[j__] = env__[i__ + j__];
		j__ += 1;
	}
	__val__[j__] = '\0';
	return (__val__);
}

int	__check__(char *__s)
{
	int	i;

	i = 0;
	if (!isalpha_or_(__s[i]))
		return (printf("0usec: export: `%s': not a valid identifier\n", __s), 0);
	while (__s[i])
	{
		if (ft_isalpha(__s[i]) || (__s[i] == '_') || ft_isdigit(__s[i]))
			i++;
		else
			return (printf("0usec: export: `%s': not a valid identifier\n", __s)
				, 0);
	}
	return (1);
}

int	__check_2__(char *__s)
{
	char	*key;

	key = 0x0;
	key = __key(__s, __find_index(__s, '='));
	if (!key)
		return (0);
	if (__check__(key))
		return (1);
	return (0);
}
