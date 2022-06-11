/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:30:52 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:30:54 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_arg(t_arg *arg)
{
	t_arg	*tmp;
	int		len;

	len = 0;
	tmp = arg;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**arg_list_to_char(t_all *all, int len)
{
	char	**arg;
	int		i;
	t_arg	*tmp;

	i = 0;
	tmp = all->arg_list;
	arg = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arg)
		return (NULL);
	while (tmp)
	{
		arg[i] = tmp->str;
		i++;
		tmp = tmp->next;
	}
	arg[i] = NULL;
	return (arg);
}

void	init_all_after_pipe(t_all *all)
{
	all->fd_in = -1;
	all->fd_add_out = -1;
	all->fd_out = -1;
}

void	list_arg_to_list_pipe(t_all *all)
{
	int		len;
	char	**ar;

	len = len_arg(all->arg_list);
	ar = arg_list_to_char(all, len);
	if (!(all->pipex))
		all->pipex = new_pipex(all, ar);
	else
	{
		addback_pipex(&all->pipex, new_pipex(all, ar));
		all->pipe = 1;
	}
	all->pipe_id++;
	argv_list_free(all, 0);
	init_all_after_pipe(all);
}

char	*parse_pipe(char *str, int *i, t_all *all)
{
	char	*one;
	int		index;

	index = *i;
	one = ft_substr(str, 0, index);
	index++;
	if (ft_strlen(one))
		write_arg_in_list(all, one);
	free(one);
	one = NULL;
	list_arg_to_list_pipe(all);
	while (str[index] == ' ')
		index++;
	(*i) = -1;
	if (str[index])
		one = ft_substr(str, index, ft_strlen(str + index));
	free(str);
	str = NULL;
	return (one);
}
