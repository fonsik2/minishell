/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:26:51 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:26:55 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_lst(char *str, t_all *all)
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
	g_exit_status = 0;
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
