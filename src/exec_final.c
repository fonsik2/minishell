/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_final.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:28:03 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:28:08 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_final(t_all *all)
{
	char	*full_path;
	char	**env;

	full_path = get_path_exec(all);
	init_fd_pipe(all, all->pipe_fd_in, all->pipe_fd_out);
	if (init_fd_redirects(all->pipex->fd_in,
			all->pipex->fd_out, all->pipex->fd_add_out))
		exit(1);
	env = make_env(all->list_envp, all);
	execve(full_path, all->pipex->arg, env);
	printf(ER_NAME": %s\n", strerror(errno));
	free(full_path);
	ft_free(env);
	exit(127);
}

void	exec_final(t_all *all)
{
	int		status;
	pid_t	pid;

	g_exit_status = 0;
	handle_signals_in_proc();
	pid = fork();
	if (pid == -1)
	{
		perror(ER_NAME);
		g_exit_status = 1;
		return ;
	}
	if (!pid)
		child_final(all);
	else
	{
		close_fds(all->pipex->fd_in,
			all->pipex->fd_out, all->pipex->fd_add_out);
		waitpid(pid, &status, 0);
		if (g_exit_status != 130 && g_exit_status != 131)
			g_exit_status = WEXITSTATUS(status);
	}
}
