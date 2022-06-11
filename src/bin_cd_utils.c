/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:13:44 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/29 21:21:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_chdir(char *str, t_all *all)
{
	if (chdir(str) == -1)
	{
		ft_putstr_fd(ER_NAME": cd: ", 2);
		perror(all->pipex->arg[1]);
		g_exit_status = 1;
		return (-1);
	}
	return (0);
}

void	add_new_pwd(t_all *all, char *old_pwd, char *pwd)
{
	t_env	*tmp;

	tmp = all->list_envp;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, "PWD")))
		{
			if (pwd)
			{
				free(tmp->value);
				tmp->value = ft_strdup(pwd);
			}
		}
		if (!(ft_strcmp(tmp->name, "OLDPWD")))
		{
			if (old_pwd)
			{
				free(tmp->value);
				tmp->value = ft_strdup(old_pwd);
			}
		}
		tmp = tmp->next;
	}
	free(old_pwd);
	free(pwd);
}

int	print_home_not_set(void)
{
	ft_putstr_fd(ER_NAME": cd: HOME not set\n", 2);
	g_exit_status = 1;
	return (-1);
}

int	check_after_cd_one(t_all *all, int *find)
{
	t_env	*tmp;

	tmp = all->list_envp;
	if ((!(ft_strcmp(all->pipex->arg[1], "~")) || (!all->pipex->arg[1])))
	{
		*find = 1;
		while (tmp)
		{
			if (!(ft_strcmp(tmp->name, "HOME")))
			{
				if (ft_chdir(tmp->value, all) == -1)
					return (-1);
				return (0);
			}
			tmp = tmp->next;
		}
		return (print_home_not_set());
	}
	else if (!(ft_strcmp(all->pipex->arg[1], "/")))
	{
		*find = 1;
		if (ft_chdir("/", all) == -1)
			return (-1);
	}
	return (0);
}

int	check_after_cd_three(t_all *all, int *find, int flag)
{
	t_env	*tmp;

	tmp = all->list_envp;
	if (!ft_strcmp(all->pipex->arg[1], "-"))
	{
		*find = 1;
		while (tmp)
		{
			if (!(ft_strcmp(tmp->name, "OLDPWD")))
			{
				flag = 1;
				if (ft_chdir(tmp->value, all) == -1)
					return (-1);
			}
			tmp = tmp->next;
		}
		if (!flag)
		{
			ft_putstr_fd(ER_NAME": cd: OLDPWD not set\n", 2);
			g_exit_status = 1;
			return (-1);
		}
	}
	return (0);
}
