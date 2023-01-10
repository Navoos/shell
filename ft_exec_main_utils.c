/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_main_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:09:08 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/10 17:48:04 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *cmd, char *arg)
{
	ft_putstr_fd("bigshell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	g_minishell.exit_status = 1;
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (errno == 2)
	{
		g_minishell.exit_status = 127;
		if (ft_strchr(cmd, '/') || !ft_strcmp(cmd, "cd"))
			ft_putstr_fd("No such file or directory\n", 2);
		else
			ft_putstr_fd("command not found\n", 2);
	}
	else if (errno == 13)
	{
		ft_putstr_fd("Permission denied\n", 2);
		g_minishell.exit_status = 126;
	}
	else
		ft_putstr_fd("error\n", 2);
}

void	ft_exec_cmd(t_shell *shell, char *_cmd, char **arglv, char **envp)
{
	char	*path;
	int		status;

	path = NULL;
	g_minishell.print_prompt = 0;
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(get_path(shell->env_head, _cmd), arglv, envp);
		ft_putstr_fd("bigshell: ", 2);
		perror(_cmd);
		exit(126 + (errno == 2));
	}
	wait(&status);
	g_minishell.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_minishell.exit_status = WTERMSIG(status) + 128;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_exec_sigint);
}

int	ft_get_argc(t_cmd *cmd)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
		tmp = tmp->next + 0 * i++;
	return (i);
}

char	**ft_get_args(t_cmd *cmd)
{
	char	**args;
	int		i;

	i = ft_get_argc(cmd);
	args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!args)
		exit(1);
	i = 0;
	while (cmd)
	{
		args[i] = cmd->val;
		cmd = cmd->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
