/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:34:44 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:34:47 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	envp_list_free(t_all *all)
{
	t_env	*tmp;

	while (all->list_envp)
	{
		tmp = all->list_envp->next;
		free(all->list_envp->name);
		free(all->list_envp->value);
		free(all->list_envp);
		all->list_envp = NULL;
		all->list_envp = tmp;
	}
}

void	argv_list_free(t_all *all, int flag)
{
	t_arg	*po;

	while (all->arg_list)
	{
		po = all->arg_list->next;
		if (flag == 1)
			free(all->arg_list->str);
		free(all->arg_list);
		all->arg_list = NULL;
		all->arg_list = po;
	}
	all->arg_list = NULL;
}

void	pipe_list_free(t_all *all)
{
	t_pipe	*tmp;

	while (all->pipex)
	{
		tmp = all->pipex->next;
		ft_free(all->pipex->arg);
		all->pipex->arg = NULL;
		free(all->pipex);
		all->pipex = NULL;
		all->pipex = tmp;
	}
	if (all->here_doc)
	{
		unlink(all->here_doc);
		free(all->here_doc);
		all->here_doc = NULL;
	}
}

void	free_all(t_all *all)
{
	if (all->path)
		ft_free(all->path);
	envp_list_free(all);
	argv_list_free(all, 0);
	pipe_list_free(all);
}
