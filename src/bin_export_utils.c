/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:26:20 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:26:32 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_nul(t_env *this_name)
{
	while (this_name)
	{
		this_name->index = 0;
		this_name = this_name->next;
	}
}

int	set_index(t_all *all)
{
	t_env	*this_name;
	t_env	*next_name;

	this_name = all->list_envp;
	next_name = all->list_envp->next;
	if ((!this_name) && (!next_name))
		return (-1);
	set_nul(this_name);
	this_name = all->list_envp;
	while (this_name)
	{
		next_name = all->list_envp;
		while (next_name)
		{
			if (ft_strcmp(this_name->name, next_name->name) > 0)
				this_name->index++;
			next_name = next_name->next;
		}
		this_name = this_name->next;
	}
	return (0);
}

void	print_env(int fd, t_env *tmp)
{
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(tmp->name, fd);
	if (tmp->value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(tmp->value, fd);
		ft_putstr_fd("\"\n", fd);
	}
	else
		ft_putstr_fd("\n", fd);
}

void	print_sorted_env(t_all *all)
{
	int		print;
	t_env	*tmp;
	int		fd;

	fd = choose_fd(all);
	print = 0;
	tmp = all->list_envp;
	if (set_index(all) == -1)
		return ;
	while (tmp)
	{
		if (print == tmp->index)
		{
			print_env(fd, tmp);
			print++;
			tmp = all->list_envp;
			continue ;
		}
		tmp = tmp->next;
	}
	g_exit_status = 0;
	close_fds(all->pipex->fd_in, all->pipex->fd_out, all->pipex->fd_add_out);
	close_two_fds(all->pipe_fd_in, all->pipe_fd_out);
}

t_env	*newlst_without_equal(char *str)
{
	int		i;
	t_env	*new;

	i = 0;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (get_name(new, str, &i, '\0'))
		return (NULL);
	new->value = NULL;
	new->next = NULL;
	new->index = 0;
	return (new);
}
