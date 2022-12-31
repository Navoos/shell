/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:05:51 by machlouj          #+#    #+#             */
/*   Updated: 2022/12/30 11:48:23 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**ft_mod_split(char *str)
// {
// 	char	*cmd;
// 	char	*arg;
// 	int		i;

// 	cmd = 0x0;
// 	arg = 0x0;
// 	if (!str)
// 		exit(1);
// 	i = 0;
// 	while (str[i] && str[i] != ' ')
// 		i += 1;
// 	if (i > 0)
// 	{
// 		cmd = ft_collect_tmp_mem(ft_strndup(str, i));
// 		arg = ft_collect_tmp_mem(ft_strndup(&str[i + 1],
// 					ft_strchr(str, 0) - &str[i + 2]));
// 	}
// 	if (arg && *arg != 0)
// 		return (__norm_ft_mod_split_arg(cmd, arg));
// 	else
// 		return (__norm_ft_mod_split_no_arg(cmd));
// }

// void	s__exec__(t_exec_node *__cmd, t_env_list **__env)
// {
// 	char	**__cmd__;
// 	char	**__tmp__;
// 	int		i;

// 	__cmd__ = 0x0;
// 	if ((__cmd && __cmd->cmd && !__cmd->cmd[0]))
// 		return ;
// 	i = 0;
// 	__cmd__ = ft_collect_tmp_mem(ft_mod_split(__cmd->cmd));
// 	__tmp__ = __cmd__;
// 	(void)__env;
// 	__signal__();
// 	if (__cmd__ && __verify__builtin__(__cmd__))
// 		__builtin__(__cmd__, __env);
// 	else if (__cmd__ && __cmd__[0])
// 		__exec__(__cmd__, __env);
// 	else
// 		ft_putstr_fd("0usec: : command not found", STDERR_FILENO);
// }

// void	__exec__(char **__cmd, t_env_list **__env)
// {
// 	int	__s;
// 	int	__i;

// 	__s = 0;
// 	__i = 0;
// 	__i = fork();
// 	if (__i < 0)
// 	{
// 		perror("ERROR");
// 		return ;
// 	}
// 	if (__i == 0)
// 	{
// 		if (__error__(__cmd, *__env))
// 			__error_norm(__cmd[0]);
// 		exit(127);
// 	}
// 	else
// 	{
// 		wait(&__s);
// 		if (WIFEXITED(__s))
// 			g_minishell.exit_status = WEXITSTATUS(__s);
// 		else if (WIFSIGNALED(__s))
// 			__signal__status__(__s);
// 	}
// }

// char	*__valid__path(t_env_list *__env)
// {
// 	char	*__work;

// 	__work = 0;
// 	while (__env)
// 	{
// 		if (!ft_strcmp(__env->key, "PATH"))
// 			return (__work = ft_collect_tmp_mem(ft_strdup
// 					(__env->value)), __work);
// 		__env = __env->next;
// 	}
// 	return (NULL);
// }

// char	*__execv__(char **s, t_env_list *__env)
// {
// 	char	*found;
// 	char	*__valid__;
// 	char	**path;
// 	int		i;

// 	__valid__ = __valid__path(__env);
// 	path = ft_collect_tmp_mem(ft_split(__valid__, ':'));
// 	norm_tmp(path);
// 	i = 0;
// 	while (path && path[i])
// 	{
// 		if (!access((char *) ft_collect_tmp_mem(ft_strjoin((char *)
// 						ft_collect_tmp_mem(ft_strjoin(path[i], "/")),
// 						s[0])), X_OK))
// 			return (found = ft_collect_tmp_mem((char *)
// 					ft_strjoin((char *) ft_collect_tmp_mem
// 						(ft_strjoin(path[i], "/")), s[0])), found);
// 		i++;
// 	}
// 	return (NULL);
// }
