/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_main_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzridi <mzridi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 19:09:08 by mzridi            #+#    #+#             */
/*   Updated: 2023/01/07 19:10:32 by mzridi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cmd(t_shell *shell, char *_cmd, char **arglv, char **envp)
{
	int	status;

	g_minishell.print_prompt = 0;
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(get_path(shell->env_head, _cmd), arglv, envp);
		perror(_cmd);
		exit(1);
	}
	wait(&status);
	g_minishell.exit_status = WEXITSTATUS(status);
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
