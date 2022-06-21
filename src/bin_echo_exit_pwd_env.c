/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo_exit_pwd_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:25:26 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/21 10:39:16 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_all *all, int i, int option, int fd)
{
	t_pipe	*tmp;

	tmp = all->pipex;
	if (!(tmp->arg[1]))
	{
		fd = choose_fd(all);
		write(fd, "\n", 1);
		close_five_fd(all);
		return ;
	}
	while (!(ft_strcmp(tmp->arg[++i], "-n")))
		option = 1;
	fd = choose_fd(all);
	while (tmp->arg[i])
	{
		ft_putstr_fd(tmp->arg[i], fd);
		if (tmp->arg[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!option)
		write(fd, "\n", 1);
	close_five_fd(all);
	g_exit = 0;
}

void	builtin_exit(t_all *all)
{
	int	len_arg;

	if (all->pipe)
		return ;
	ft_putstr_fd("exit\n", 1);
	len_arg = len_str(all->pipex->arg);
	if (len_arg == 1)
		exit(0);
	else if (len_arg == 2 && str_is_num(all->pipex->arg[1]))
		exit(ft_atoi(all->pipex->arg[1]));
	else if (len_arg > 1 && !(str_is_num(all->pipex->arg[1])))
	{
		ft_putstr_fd(ER_NAME": exit: ", 2);
		ft_putstr_fd(all->pipex->arg[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (len_arg > 2 && str_is_num(all->pipex->arg[1]))
	{
		ft_putstr_fd(ER_NAME": exit: ", 2);
		ft_putstr_fd(": too many arguments\n", 2);
		g_exit = 1;
	}
}

void	builtin_pwd(t_all *all)
{
	char	*dir;
	int		fd;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_putstr_fd(ER_NAME": ", 2);
		perror("pwd: ");
		g_exit = 127;
		return ;
	}
	fd = choose_fd(all);
	ft_putstr_fd(dir, fd);
	ft_putstr_fd("\n", fd);
	free(dir);
	g_exit = 0;
	close_five_fd(all);
}

static void	env_print_error(char *str)
{
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit = 127;
}

void	builtin_env(t_all *all, int fd)
{
	t_env	*tmp;

	tmp = all->list_envp;
	if (all->pipex->arg[1])
	{
		env_print_error(all->pipex->arg[1]);
		return ;
	}
	fd = choose_fd(all);
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->name, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(tmp->value, fd);
			ft_putstr_fd("\n", fd);
		}
		tmp = tmp->next;
	}
	g_exit = 0;
	close_five_fd(all);
}
