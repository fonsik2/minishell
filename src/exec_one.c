/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 15:13:52 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/27 15:13:54 by ephantom         ###   ########.fr       */
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

void	child_one(t_all *all)
{
	char	*full_path;
	char	**env;

	{
		full_path = get_path_exec(all);
		if (init_fd_redirects(all->pipex->fd_in,
				all->pipex->fd_out, all->pipex->fd_add_out))
			exit(1);
		env = make_env(all->list_envp, all);
		if (execve(full_path, all->pipex->arg, env) == -1) //execute a file
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
		child_one(all);
	else
	{
		waitpid(pid, &status, 0); //wait for child procces
		if (g_exit_status != 130 && g_exit_status != 131)
			g_exit_status = WEXITSTATUS(status);
		close_fds(all->pipex->fd_in,
			all->pipex->fd_out, all->pipex->fd_add_out);
	}
	handler_sig();
}
