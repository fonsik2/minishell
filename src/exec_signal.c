/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:28:49 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/18 21:07:30 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_sigquit_proc(int sig)
{
	printf("Quit: %d\n", sig);
	g_exit = 131;
}

static void	my_sigint_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_exit = 130;
	}
}

void	handle_signals_in_proc(void)
{
	signal(SIGQUIT, my_sigquit_proc);
	signal(SIGINT, my_sigint_proc);
}

void	my_sign_here(int i)
{
	if (i == SIGINT)
	{
		write(2, ">                            \n", 30);
		exit(1);
	}
}
