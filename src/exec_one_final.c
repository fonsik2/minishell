/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_final.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:28:27 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/21 16:26:28 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_exec(t_all *all)
{
	char	*full_path;

	if (!all->pipex->arg[0][0])
	{
		ft_putstr_fd(ER_NAME": ", 2);
		ft_putstr_fd(all->pipex->arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	full_path = get_path_for_exec(all, all->pipex->arg);
	if (!full_path)
	{
		ft_putstr_fd(ER_NAME": ", 2);
		ft_putstr_fd(all->pipex->arg[0], 2);
		if (ft_strchr(all->pipex->arg[0], '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	return (full_path);
}

static void	child_one(t_all *all)
{
	char	*full_path;
	char	**env;

	{
		full_path = get_path_exec(all);
		if (init_fd_redirects(all->pipex->fd_in,
				all->pipex->fd_out, all->pipex->fd_add_out))
			exit(1);
		env = make_env(all->list_envp, all);
		if (execve(full_path, all->pipex->arg, env) == -1)
		{
			printf(ER_NAME": %s\n", strerror(errno));
			free(full_path);
			ft_free(env);
			exit(127);
		}
	}
}

void	exec_one(t_all *all)
{
	int		status;
	pid_t	pid;

	g_exit = 0;
	handle_signals_in_proc();
	pid = fork();
	if (pid == -1)
	{
		perror(ER_NAME);
		g_exit = 1;
		return ;
	}
	if (!pid)
		child_one(all);
	else
	{
		waitpid(pid, &status, 0);
		if (g_exit != 130 && g_exit != 131)
			g_exit = WEXITSTATUS(status);
		close_fds(all->pipex->fd_in,
			all->pipex->fd_out, all->pipex->fd_add_out);
	}
	handler_signal();
}

static void	child_final(t_all *all)
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

	g_exit = 0;
	handle_signals_in_proc();
	pid = fork();
	if (pid == -1)
	{
		perror(ER_NAME);
		g_exit = 1;
		return ;
	}
	if (!pid)
		child_final(all);
	else
	{
		close_fds(all->pipex->fd_in,
			all->pipex->fd_out, all->pipex->fd_add_out);
		waitpid(pid, &status, 0);
		if (g_exit != 130 && g_exit != 131)
			g_exit = WEXITSTATUS(status);
	}
}
