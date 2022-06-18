/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list_new.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:35:01 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/18 19:33:13 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	*argnew(char *s)
{
	t_arg	*arg_list;

	arg_list = (t_arg *)malloc(sizeof(t_arg));
	if (!arg_list)
		return (NULL);
	arg_list->str = ft_strdup(s);
	arg_list->next = NULL;
	return (arg_list);
}

static void	addback_argnew(t_arg **arg_list, t_arg *new)
{
	t_arg	*el;

	if (!new || !arg_list)
		return ;
	if (!(*arg_list))
	{
		*arg_list = new;
		return ;
	}
	el = *arg_list;
	while (el->next)
		el = el->next;
	el->next = new;
}

void	write_arg_in_list(t_all *all, char *str)
{
	if (!all->arg_list)
		all->arg_list = argnew(str);
	else
		addback_argnew(&all->arg_list, argnew(str));
}

t_pipe	*new_pipex(t_all *all, char **ar)
{
	t_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_pipe));
	if (!new_pipe)
		return (NULL);
	new_pipe->pipe_id = all->pipe_id;
	new_pipe->fd_in = all->fd_in;
	new_pipe->fd_out = all->fd_out;
	new_pipe->fd_add_out = all->fd_add_out;
	new_pipe->arg = ar;
	new_pipe->next = NULL;
	new_pipe->pid = -1;
	return (new_pipe);
}

void	addback_pipex(t_pipe **pipex, t_pipe *new)
{
	t_pipe	*tmp;

	if (!new || !pipex)
		return ;
	if (!(*pipex))
	{
		(*pipex) = new;
		return ;
	}
	tmp = *pipex;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
