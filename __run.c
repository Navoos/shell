/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __run.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yakhoudr <yakhoudr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:34:18 by machlouj          #+#    #+#             */
/*   Updated: 2022/10/08 16:16:41 by yakhoudr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_exec(t_tree *a, int level)
{
	int			i;
	t_exec_node	*enode;

	i = -1;
	while (++i < level)
		printf("\t");
	enode = (t_exec_node *) a;
	printf("EXEC :\t%s\n", enode->cmd);
}

void	ft_print_tree(t_tree *tree, t_env_list **env)
{
	if (tree && tree->type == PNODE && !g_minishell.error_flag)
		__pipe__(tree, env);
	else if (tree && tree->type == ENODE && !g_minishell.error_flag)
		s__exec__((t_exec_node *)tree, env);
	else if (tree && tree->type == RNODE && !g_minishell.error_flag)
		__redir__((t_redir_node *)tree, env);
}
