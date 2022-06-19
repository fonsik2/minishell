/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:33:47 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/19 17:24:50 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_forbidden_symbols(char *str, int one, int two, int i)
{
	if (ft_strchr(str, ';'))
		return (-1);
	if (ft_strchr(str, '\\'))
		return (-11);
	while (str[++i])
	{
		if (str[i] == '\'' && !one && !two)
			one++;
		else if (str[i] == '\"' && !one && !two)
			two++;
		else if (str[i] == '\'' && (one == 1) && !two)
			one--;
		else if (str[i] == '\"' && !one && (two == 1))
			two--;
	}
	if (one)
		return (-2);
	if (two)
		return (-3);
	return (0);
}

int	check_closed_quote(int result)
{
	if (result == -1)
		ft_putstr_fd(ER_NAME": syntax error near unexpected token ';'\n", 2);
	if (result == -11)
		ft_putstr_fd(ER_NAME": syntax error near unexpected token '\\'\n", 2);
	else if (result == -2)
		ft_putstr_fd(ER_NAME": syntax error: unexpected end of file\n", 2);
	else if (result == -3)
		ft_putstr_fd(ER_NAME": syntax error: unclosed \" double quote\n", 2);
	if (result < 0)
	{
		g_exit = 1;
		return (1);
	}
	return (0);
}

static void	token_pipe(char *str, int i)
{
	if (str[i + 1] == '|')
		ft_putstr_fd(ER_NAME
			": syntax error near unexpected token '||'\n", 2);
	else
		ft_putstr_fd(ER_NAME
			": syntax error near unexpected token '|'\n", 2);
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
