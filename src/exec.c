/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:27:39 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/20 20:40:52 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_pipe(t_all *all)
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

static void	parent_pipe(t_all *all, pid_t pid)
{
	all->pipex->pid = pid;
	close(all->pipe_fd_out);
	dup2(all->pipe_fd_in, all->tmp_in);
	close(all->pipe_fd_in);
	close(all->pipe_fd_out);
	close_fds(all->pipex->fd_in,
		all->pipex->fd_out, all->pipex->fd_add_out);
}

static void	exec_pipe(t_all *all)
{
	pid_t	pid;

	handle_signals_in_proc();
	if (init_pipe_for_fd(all) == 1)
	{
		g_exit = 1;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(ER_NAME);
		g_exit = 1;
		return ;
	}
	if (!pid)
		child_pipe(all);
	else
		parent_pipe(all, pid);
}

static void	pipeline(t_all *all)
{
	t_pipe	*tmp;
	int		status;

	tmp = all->pipex;
	all->tmp_in = dup(STDIN_FILENO);
	while (all->pipex->next)
	{
		if (builtin(all))
			exec_pipe(all);
		all->pipex = all->pipex->next;
	}
	if (builtin(all))
		exec_final(all);
	else
		close(all->tmp_in);
	while (tmp)
	{
		if (tmp->pid != -1)
			kill(tmp->pid, 15);
		tmp = tmp->next;
	}
	while (waitpid(-1, &status, 0) > 0)
		;
}

void	exec_module(t_all *all)
{
	int		size;

	if (all->pipex->arg)
	{
		size = len_pipex(all->pipex);
		if (size == 1)
		{
			if (builtin(all))
				exec_one(all);
		}
		else
			pipeline(all);
		all->pipe = 0;
	}
}
