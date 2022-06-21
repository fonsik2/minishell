/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:33:47 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/21 15:15:23 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_pipe(char *str, int i)
{
	if (str[i + 1] == '|')
		ft_putstr_fd(ER_NAME
			": syntax error near unexpected token '||'\n", 2);
	else
		ft_putstr_fd(ER_NAME
			": syntax error unexpected token `|'\n", 2);
	g_exit = 258;
}

static int	print_unclosed_pipe(char *check_str)
{
	ft_putstr_fd(ER_NAME": error: unclosed pipe\n", 2);
	g_exit = 258;
	free(check_str);
	return (1);
}

int	check_empty_pipe(char *str, int i)
{
	int		check;
	char	*check_str;

	check = 0;
	while (str[++i])
	{
		if (str[i] != '|' && str[i] != ' ')
			check = 1;
		if (str[i] == '|')
		{
			if (check == 0)
			{
				token_pipe(str, i);
				return (1);
			}
			check_str = ft_strtrim(str + i + 1, " ");
			if (ft_strlen(check_str) == 0)
				return (print_unclosed_pipe(check_str));
			check = 0;
			free(check_str);
			check_str = NULL;
		}
	}
	return (0);
}
