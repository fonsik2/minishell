/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:13:27 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/29 12:17:15 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe_for_fd(t_all *all)
{
	int	pipe_fd[2];

	if (all->pipe)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror(ER_NAME);
			return (1);
		}
		all->pipe_fd_in = pipe_fd[0];
		all->pipe_fd_out = pipe_fd[1];
	}
	return (0);
}

int	choose_fd(t_all *all)
{
	int	fd;

	fd = 1;
	if (all->pipe)
	{
		if (all->pipex->pipe_id == all->pipe_id - 1)
			fd = 1;
		else
		{
			init_pipe_for_fd(all);
			dup2(all->pipe_fd_in, all->tmp_in);
			fd = all->pipe_fd_out;
		}
	}
	if (all->pipex->fd_out != -1)
		fd = all->pipex->fd_out;
	if (all->pipex->fd_add_out != -1)
		fd = all->pipex->fd_add_out;
	return (fd);
}

void	close_two_fds(int fd1, int fd2)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}

int	builtin(t_all *all)
{
	if (!(all->pipex->arg[0]))
		return (1);
	if (ft_strcmp(all->pipex->arg[0], "pwd") == 0)
		builtin_pwd(all);
	else if (ft_strcmp(all->pipex->arg[0], "echo") == 0)
		builtin_echo(all, 0, 0, 1);
	else if (ft_strcmp(all->pipex->arg[0], "env") == 0)
		builtin_env(all, 1);
	else if (ft_strcmp(all->pipex->arg[0], "export") == 0)
		builtin_export(all);
	else if (ft_strcmp(all->pipex->arg[0], "unset") == 0)
		builtin_unset(all, 0);
	else if (ft_strcmp(all->pipex->arg[0], "cd") == 0)
		builtin_cd(all);
	else if (ft_strcmp(all->pipex->arg[0], "exit") == 0)
		builtin_exit(all);
	else
		return (1);
	return (0);
}
