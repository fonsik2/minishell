/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:29:36 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/18 12:04:18 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_five_fd(t_all *all)
{
	close_fds(all->pipex->fd_in, all->pipex->fd_out, all->pipex->fd_add_out);
	close_two_fds(all->pipe_fd_in, all->pipe_fd_out);
}

void	init_fd_pipe(t_all *all, int fd_in, int fd_out)
{
	if (all->pipex->pipe_id == 0)
	{
		close(fd_in);
		dup2(fd_out, 1);
		close(fd_out);
		close(all->tmp_in);
	}
	else if (all->pipex->pipe_id == all->pipe_id - 1)
	{
		close(fd_out);
		dup2(all->tmp_in, 0);
		close(all->tmp_in);
	}
	else
	{
		dup2(fd_out, 1);
		dup2(all->tmp_in, 0);
		close(fd_out);
		close(all->tmp_in);
	}
}

void slash(t_all *all)
{
	int i;
	char	*buf;

	i = -1;
	while (all->envp[++i])
	{
		buf = all->envp[i];
		all->envp[i] = ft_strjoin(buf, "/");
		free(buf);
	}
}
