/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:09:50 by yakhoudr          #+#    #+#             */
/*   Updated: 2022/10/09 22:02:59 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i += 1;
	return (s1[i] - s2[i]);
}

char	*get_cor_value(char *key, t_env_list *env_list)
{
	char	*res;

	while (env_list)
	{
		if (!(ft_strcmp(key, env_list->key)))
			return (env_list->value);
		env_list = env_list->next;
	}
	res = ft_collect_tmp_mem(ft_strdup(""));
	return (res);
}

int	ft_increase_normal_char(char *str, char **res)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '$')
		i += 1;
	tmp = ft_collect_tmp_mem(ft_strndup(str, i));
	*res = ft_collect_tmp_mem(ft_strjoin(*res, tmp));
	return (i);
}

int	ft_get_new_string(char *str, char **res, t_env_list *env_list)
{
	char	*key;
	int		j;

	j = 0;
	while (str[j] && str[j] != ' ' && str[j] != '$')
		j += 1;
	key = ft_collect_tmp_mem(ft_strndup(str, j));
	*res = ft_collect_tmp_mem(ft_strjoin(*res, get_cor_value(key, env_list)));
	return (j);
}

void	ft_get_exit_status(char **res, int *i)
{
	char	*nb;

	nb = ft_collect_tmp_mem(ft_itoa(g_minishell.exit_status));
	*res = ft_collect_tmp_mem(ft_strjoin(*res, nb));
	(*i)++;
}
