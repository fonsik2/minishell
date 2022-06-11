/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:28:49 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:29:00 by smdyan           ###   ########.fr       */
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
