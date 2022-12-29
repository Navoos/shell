/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:12:53 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/09 21:49:31 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_equal(char const *s1, char const *s2)
{
	if (!s2)
		return (0x0);
	else
		return ((char *) ft_collect_tmp_mem(ft_strjoin((char *)
					ft_collect_tmp_mem(ft_strjoin(s1, "=")), s2)));
}

int	__env__len(t_env_list *__env__)
{
	int	i;

	i = 0;
	while (__env__)
	{
		i++;
		__env__ = __env__->next;
	}
	return (i);
}

char	**env_path(t_env_list *__env__)
{
	char		**__path__;
	t_env_list	*__tmp__;
	int			i;

	__tmp__ = __env__;
	i = __env__len(__env__);
	__path__ = ft_collect_tmp_mem(malloc(sizeof(char *) * (i + 1)));
	if (!__path__)
		return (NULL);
	i = 0;
	while (__tmp__)
	{
		__path__[i] = ft_collect_tmp_mem((char *)
				ft_strjoin_equal(__tmp__->key, __tmp__->value));
		if (!__path__[i])
			return (NULL);
		i++;
		__tmp__ = __tmp__->next;
	}
	__path__[i++] = NULL;
	return (__path__);
}

void	__print__env(char *__key, char *__val, int s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (__key[i])
			write(1, &__key[i++], 1);
		write(1, "=", 1);
		i = 0;
		while (__val[i])
			write(1, &__val[i++], 1);
		write(1, "\n", 1);
	}
	else
	{
		i = 0;
		while (__key[i] && __val)
		{
			write(1, &__key[i++], 1);
			write(1, "=\n", 2);
		}
	}
}

void	__env__(t_env_list **__env, char **__s)
{
	t_env_list	*tmp;

	if (__s[1])
	{
		printf("env: %s: No such file or directory\n", __s[1]);
		g_minishell.exit_status = 127;
		return ;
	}
	tmp = *__env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
			__print__env(tmp->key, tmp->value, 1);
		else if (tmp->key && !tmp->value)
			__print__env(tmp->key, tmp->value, 0);
		tmp = tmp->next;
	}
	g_minishell.exit_status = 0;
}
