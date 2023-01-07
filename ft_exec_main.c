/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 11:54:03 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/07 19:09:52 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env *env_head, char *cmd)
{
	char	**env_path;

	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/')
		|| (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (cmd);
		return (0);
	}
	env_path = ft_split(ft_get_env(env_head, "PATH"), ':');
	while (*env_path)
	{
		if (access(ft_strjoin(*env_path, ft_strjoin("/", cmd)), \
				F_OK) == 0)
			return (ft_strjoin(*env_path, ft_strjoin("/", cmd)));
		env_path++;
	}
	return (0);
}

int	is_built_in(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd, "export") == 0)
		return (4);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd, "env") == 0)
		return (6);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

void	exec_built_in(int argc, char **argv, t_shell *shell)
{
	if (is_built_in(argv[0]) == 1)
		ft_echo(argc, argv);
	else if (is_built_in(argv[0]) == 2)
		ft_cd(shell, argv);
	else if (is_built_in(argv[0]) == 3)
		ft_pwd(shell);
	else if (is_built_in(argv[0]) == 4)
		ft_export(shell, argv);
	else if (is_built_in(argv[0]) == 5)
		ft_unset(shell, argv);
	else if (is_built_in(argv[0]) == 6)
		ft_print_env(shell->env_head);
	else if (is_built_in(argv[0]) == 7)
		ft_exit(argv);
}

void	exec_line(t_cmd *cmd, t_shell *shell)
{
	char	*_cmd;
	char	**envp;
	char	**arglv;
	int		arglc;

	arglc = ft_get_argc(cmd);
	arglv = ft_get_args(cmd);
	envp = ft_env_to_tab(shell->env_head);
	if (arglv && is_built_in(arglv[0]))
		exec_built_in(arglc, arglv, shell);
	else
	{
		_cmd = arglv[0];
		if (get_path(shell->env_head, _cmd))
			ft_exec_cmd(shell, _cmd, arglv, envp);
		else
		{
			ft_putstr_fd("bigshell: command not found\n", 2);
			g_minishell.exit_status = 127;
		}
	}
	free(arglv);
}

int	ft_exec_main(t_tree *tree, t_shell *shell)
{
	t_exec_node		*cnode;
	t_pipe_node		*pnode;
	t_redir_node	*rnode;

	if (tree->type == ENODE)
	{
		cnode = (t_exec_node *)tree;
		if (cnode->cmd)
			exec_line(cnode->cmd, shell);
	}
	else if (tree->type == PNODE)
	{
		pnode = (t_pipe_node *)tree;
		ft_exec_pipe(pnode, shell);
	}
	else if (tree->type == RNODE)
	{
		rnode = (t_redir_node *)tree;
		ft_redir(rnode, shell);
	}
	return (0);
}
