/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:29:17 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:29:20 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*access_find_com(char *find_com)
{
	DIR	*dr;

	if (!(access(find_com, X_OK)))
	{
		dr = opendir(find_com);
		if (dr)
		{
			ft_putstr_fd(ER_NAME": ", 2);
			ft_putstr_fd(find_com, 2);
			ft_putstr_fd(": is a directory\n", 2);
			closedir(dr);
			free(find_com);
			exit(126);
		}
		return (find_com);
	}
	return (NULL);
}

char	*get_path_for_exec(t_all *all, char **new_arg)
{
	char	*find_com;
	int		i;

	i = -1;
	if (all->path)
	{
		ft_free(all->path);
		all->path = NULL;
	}
	get_path(all, new_arg[0]);
	while (all->path[++i])
	{
		if (!(ft_strchr(new_arg[0], '/')))
			find_com = ft_strjoin(all->path[i], new_arg[0]);
		else
			find_com = ft_strdup(new_arg[0]);
		if (access_find_com(find_com))
			return (find_com);
	}
	free(find_com);
	return (NULL);
}

char	**make_env(t_env *env, t_all *all)
{
	char	**envp;
	char	*eq;
	t_env	*tmp;
	int		len;

	tmp = all->list_envp;
	len = len_env(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		exit(1);
	len = 0;
	while (tmp)
	{
		eq = ft_strjoin(tmp->name, "=");
		envp[len++] = ft_strjoin(eq, tmp->value);
		free(eq);
		tmp = tmp->next;
	}
	envp[len] = NULL;
	return (envp);
}

int	init_fd_redirects(int fd_in, int fd_out, int fd_add_out)
{
	if (fd_in != -1)
	{
		if (dup2(fd_in, 0) == -1)
			return (1);
	}
	if (fd_out != -1)
	{
		if (dup2(fd_out, 1) == -1)
			return (1);
	}
	if (fd_add_out != -1)
	{
		if (dup2(fd_add_out, 1) == -1)
			return (1);
	}
	return (0);
}

int	get_path(t_all *all, char *str)
{
	t_env	*tmp;

	tmp = all->list_envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PATH", 4) == 0)
		{
			all->path = ft_split(ft_strchr(tmp->value, '/'), ':');
			break ;
		}
		tmp = tmp->next;
	}
	if (!(all->path))
	{
		ft_putstr_fd(ER_NAME": ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		envp_list_free(all);
		exit(127);
	}
	slash(all);
	return (0);
}
