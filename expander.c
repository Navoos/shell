/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:08:50 by yakhoudr          #+#    #+#             */
/*   Updated: 2023/01/06 16:26:14 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_solo_dollar(char **res)
{
	*res = ft_collect_tmp_mem(ft_strjoin(*res, "$"));
}

void	ft_init_expander(char **res, int *i)
{
	*i = 0;
	*res = ft_collect_tmp_mem(ft_strdup(""));
}

int	ft_increase_normal_char_for_special_char(char *str, char **res)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$')
		i += 1;
	tmp = ft_collect_tmp_mem(ft_strndup(str - 1, i));
	*res = ft_collect_tmp_mem(ft_strjoin(*res, tmp));
	return (i);
}

void	__norm_expander(int *i, char *str, char **res, t_env *env_list)
{
	*i += 1;
	if (str[*i] == '?')
		ft_get_exit_status(res, i);
	else
	{
		if (str[*i])
			*i += ft_get_new_string(&str[*i], res, env_list);
		else
			ft_get_solo_dollar(res);
	}
}

char	*ft_expand(char *str, t_env *env_list)
{
	int		i;
	char	*res;

	ft_init_expander(&res, &i);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1]
			&& (str[i + 1] == '=' || str[i + 1] == '+'))
			i += ft_increase_normal_char_for_special_char(&str[i + 1], &res);
		if (str[i] == '$')
			__norm_expander(&i, str, &res, env_list);
		else
			i += ft_increase_normal_char(&str[i], &res);
	}
	return (res);
}
