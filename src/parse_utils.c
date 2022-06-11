/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:32:43 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:32:46 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_pipe_error(char *str, int i)
{
	if (str[i + 1])
		ft_putstr_fd(ER_NAME": syntax error near unexpected token `||'\n", 2);
	else
		ft_putstr_fd(ER_NAME": syntax error near unexpected token `|'\n", 2);
}

int	find_token(char *str, int i)
{
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			ft_putstr_fd(ER_NAME" :syntax error near unexpected token `>>'\n",
				2);
		else
			ft_putstr_fd(ER_NAME" :syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	else if (str[i] == '|')
	{
		print_pipe_error(str, i);
		return (1);
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			ft_putstr_fd(ER_NAME":syntax error near unexpected token`<<\''\n", 2);
		else
			ft_putstr_fd(ER_NAME":syntax error near unexpected token `<\''\n", 2);
		return (1);
	}
	return (0);
}

int	check_syntax_er(char *str, int index)
{
	if (!(ft_strlen(str + index)))
	{
		ft_putstr_fd(ER_NAME": syntax error near unexpected token `newline'\n",
			2);
		return (1);
	}
	if (find_token(str, index))
		return (1);
	return (0);
}

char	*rename_file(char *out_file, t_all *all)
{
	int	i;

	i = 0;
	while (out_file[i])
	{
		if (out_file[i] == '\'')
			out_file = parse_squote(out_file, &i, all, 0);
		else if (out_file[i] == '"')
			out_file = parse_dquote(out_file, &i, all, 0);
		else if (out_file[i] == '$')
			out_file = parse_dollar(out_file, &i, all);
		if (!out_file)
			return (NULL);
		i++;
	}
	return (out_file);
}

char	*free_null(t_all *all, char *str, char *new_str)
{
	free(str);
	str = NULL;
	free(new_str);
	new_str = NULL;
	argv_list_free(all, 1);
	pipe_list_free(all);
	return (NULL);
}
