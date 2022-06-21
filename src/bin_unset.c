/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:26:51 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/21 15:55:15 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	slash(t_all *all)
{
	int		i;
	char	*buf;

	i = -1;
	while (all->path[++i])
	{
		buf = all->path[i];
		all->path[i] = ft_strjoin(buf, "/");
		free(buf);
	}
}

static void	ft_del_lst(char *str, t_all *all)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = all->list_envp;
	prev = NULL;
	if (!tmp->next)
	{
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		return ;
	}
	while (ft_strcmp(tmp->name, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	free(tmp->name);
	free(tmp->value);
	if (!prev)
		all->list_envp = all->list_envp->next;
	else
		prev->next = tmp->next;
	free(tmp);
}

int	check_line(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (-1);
	if ((!ft_isalpha(str[0])) && str[0] != '_')
		return (-1);
	while (str[++i] && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) && str[i] != '_'))
			return (-1);
	}
	if (!(ft_strchr(str, '=')))
		return (-2);
	return (0);
}

void	builtin_unset(t_all *all, int i)
{
	t_env	*tmp;

	if (all->pipe)
		return ;
	while (all->pipex->arg[++i] && !(all->pipe))
	{
		tmp = all->list_envp;
		if (!tmp)
			return ;
		if (check_line(all->pipex->arg[i]) == -1)
		{
			export_print_error(all->pipex->arg[i]);
			continue ;
		}
		while (tmp)
		{
			if (!(ft_strcmp(all->pipex->arg[i], tmp->name)))
			{
				ft_del_lst(tmp->name, all);
				break ;
			}
			tmp = tmp->next;
		}
	}
	g_exit = 0;
}
