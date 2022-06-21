/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:04:20 by ephantom          #+#    #+#             */
/*   Updated: 2022/06/21 15:55:15 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_number_arg(int argc, char **argv)
{
	printf(COLOR "🌈 Entry\n");
	if (argc != 1)
	{
		ft_putstr_fd(COLOR ER_NAME": "END, 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
}

static void	handler_c(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "  \n", 3);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit = 1;
	}
}

void	handler_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, handler_c);
}

static void	init_struct(t_all *all)
{
	all->list_envp = NULL;
	all->here_doc = NULL;
	all->path = NULL;
	all->tmp_in = -1;
	all->fd_in = -1;
	all->fd_out = -1;
	all->fd_add_out = -1;
	all->pipe = 0;
	all->pipe_id = 0;
	all->pipe_fd_in = -1;
	all->pipe_fd_out = -1;
	all->arg_list = NULL;
	all->pipex = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_all	all;

	check_number_arg(argc, argv);
	handler_signal();
	init_struct(&all);
	if (envp_to_list(&all, envp) == 1)
		return (1);
	g_exit = 0;
	while (1)
	{
		handler_signal();
		str = readline(COLOR NAME"> "END);
		if (!str)
		{
			printf(COLOR "exit✋\n");
			break ;
		}
		if (*str)
			add_history(str);
		parser(str, &all);
		free(str);
	}
	free_all(&all);
	return (0);
}
