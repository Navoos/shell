// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   env.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/25 21:07:40 by yakhoudr          #+#    #+#             */
// /*   Updated: 2023/01/06 16:24:22 by mzridi           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// char	*ft_get_key(char *str)
// {
// 	int		i;
// 	char	*res;

// 	i = 0;
// 	while (str[i] != '=' && str[i])
// 		i += 1;
// 	res = ft_strndup((char *) str, i);
// 	return (res);
// }

// char	*ft_get_value(char *str)
// {
// 	int		i;
// 	char	*res;

// 	i = 0;
// 	while (str[i] && str[i] != '=')
// 		i += 1;
// 	res = ft_strndup((char *) str + i + 1, ft_strlen(str) - i + 1);
// 	return (res);
// }

// void	ft_add_env_entrace(t_env **env, t_env_list *env_node)
// {
// 	t_env_list	*tmp;

// 	if (!*env)
// 	{
// 		*env = env_node;
// 		return ;
// 	}
// 	tmp = *env;
// 	while (tmp->next)
// 		tmp = tmp->next;
// 	tmp->next = env_node;
// }

// t_env_list	*ft_create_env_node(char *key, char *value)
// {
// 	t_env_list	*env_node;

// 	env_node = ft_xalloc(sizeof(t_env_list));
// 	env_node->key = key;
// 	env_node->value = value;
// 	env_node->next = 0x0;
// 	ft_add_to_perm_memory(&g_minishell.perm_memory,
// 		ft_create_memory_node((void *)env_node));
// 	ft_add_to_perm_memory(&g_minishell.perm_memory,
// 		ft_create_memory_node((void *)env_node->key));
// 	ft_add_to_perm_memory(&g_minishell.perm_memory,
// 		ft_create_memory_node((void *)env_node->value));
// 	return (env_node);
// }

// void	ft_init_env_list(t_env_list **env, char **envp)
// {
// 	int	i;

// 	*env = 0x0;
// 	if (!*envp)
// 	{
// 		ft_add_env_entrace(env,
// 			ft_create_env_node(ft_strdup("PWD"), (getcwd(NULL, 0))));
// 		ft_add_env_entrace(env,
// 			ft_create_env_node(ft_strdup("SHLVL"), ft_strdup("1")));
// 		ft_add_env_entrace(env,
// 			ft_create_env_node(ft_strdup("_"), ft_strdup("/usr/bin/env")));
// 	}
// 	else
// 	{
// 		i = 0;
// 		while (envp[i])
// 		{
// 			ft_add_env_entrace(env,
// 				ft_create_env_node(ft_get_key(envp[i]), ft_get_value(envp[i])));
// 			i += 1;
// 		}
// 	}
// }
