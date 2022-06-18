/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:24:32 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/18 20:58:34 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd(int flag)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		if (flag)
		{
			ft_putstr_fd(ER_NAME": ", 2);
			perror("cd: ");
		}
		g_exit = 127;
		return (NULL);
	}
	return (dir);
}

static void	check_oldpwd(t_all *all)
{
	t_env	*tmp;
	int		flag;

	flag = 0;
	tmp = all->list_envp;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, "OLDPWD")))
			flag = 1;
		tmp = tmp->next;
	}
	if (!flag)
		ft_lstadd_back(&all->list_envp, ft_lstnew("OLDPWD= ", 0));
}

static int	check_after_cd_two(t_all *all, int *find)
{
	char	*dir;
	char	*s;
	int		len;

	if (!(ft_strcmp(all->pipex->arg[1], "..")))
	{
		*find = 1;
		dir = get_pwd(1);
		if (!dir)
			return (-1);
		len = ft_strlen(dir)
			- ft_strlen(ft_strrchr(dir, '/'));
		s = ft_substr(dir, 0, len);
		free(dir);
		if (ft_chdir(s, all) == -1)
			return (-1);
		free(s);
	}
	return (0);
}

static void	end_cd(t_all *all, char *old_pwd)
{
	char	*pwd;

	pwd = get_pwd(1);
	check_oldpwd(all);
	add_new_pwd(all, old_pwd, pwd);
	g_exit = 0;
}

void	builtin_cd(t_all *all)
{
	char	*old_pwd;
	int		find;

	find = 0;
	if (all->pipe)
		return ;
	old_pwd = get_pwd(0);
	if (check_after_cd_one(all, &find) == -1
		|| check_after_cd_two(all, &find) == -1
		|| check_after_cd_three(all, &find, 0) == -1)
	{
		free(old_pwd);
		return ;
	}
	if (ft_strcmp(all->pipex->arg[1], ".") && !find)
	{
		if (ft_chdir(all->pipex->arg[1], all) == -1)
		{
			free(old_pwd);
			return ;
		}
	}
	end_cd(all, old_pwd);
}
