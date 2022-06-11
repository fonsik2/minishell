/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:03:50 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/26 01:01:47 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_sigquit_proc(int sig)
{
	printf("Quit: %d\n", sig);
	g_exit_status = 131;
}

void	my_sigint_proc(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 1);
		g_exit_status = 130;
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
