/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:33:20 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/20 20:58:51 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parser_str(t_all *all, char *str, int i)
{
	while (str[i])
	{
		if (str[i] == ' ')
			str = parse_space(str, &i, all);
		else if (str[i] == '\'')
			str = parse_squote(str, &i, all, 1);
		else if (str[i] == '"')
			str = parse_dquote(str, &i, all, 1);
		else if (str[i] == '$')
			str = parse_dollar(str, &i, all);
		else if (str[i] == '>' || str[i] == '<')
			str = parse_redirect(str, &i, all);
		else if (str[i] == '|')
			str = parse_pipe(str, &i, all);
		if (!str)
			return (NULL);
		i++;
	}
	if (ft_strlen(str) != 0)
		write_arg_in_list(all, str);
	list_arg_to_list_pipe(all);
	return (str);
}

static void	new_str_null(t_all *all)
{
	all->pipe_id = 0;
	argv_list_free(all, 0);
	pipe_list_free(all);
	if (g_exit != 1)
		g_exit = 258;
}

static void	exec_and_free(t_all *all, char *new_str)
{
	t_pipe	*tmp;

	tmp = all->pipex;
	exec_module(all);
	all->pipex = tmp;
	pipe_list_free(all);
	free(new_str);
	new_str = NULL;
}

void	parser(char *str, t_all *all)
{
	char	*new_str;

	new_str = ft_strtrim(str, " ");
	if (!new_str)
	{
		g_exit = 258;
		return ;
	}
	if (check_empty_pipe(new_str, -1))
	{
		free(new_str);
		new_str = NULL;
		return ;
	}
	new_str = parser_str(all, new_str, 0);
	if (!new_str)
	{
		new_str_null(all);
		return ;
	}
	exec_and_free(all, new_str);
}

int	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*el;

	if (!new || !lst)
		return (1);
	if (!(*lst))
	{
		*lst = new;
		return (0);
	}
	el = *lst;
	while (el->next)
		el = el->next;
	el->next = new;
	return (0);
}
