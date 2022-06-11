/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:25:54 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:25:58 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_newlst_name(char *str, int status, int i, int len)
{
	char	*name;

	while (str[++i] && str[i] != '=')
		len++;
	if (status)
	{
		name = malloc(sizeof(char) * (len + 1));
		if (!name)
			return (NULL);
		i = -1;
		while (str[++i] && str[i] != '=')
			name[i] = str[i];
		name[i] = '\0';
	}
	else
	{
		name = malloc(sizeof(char) * ft_strlen((str + len + 1) + 1));
		if (!name)
			return (NULL);
		i = -1;
		while (str[++len])
			name[++i] = str[len];
		name[++i] = '\0';
	}
	return (name);
}

static void	add_list(int status, t_all *all, char *str)
{
	if (status)
		ft_lstadd_back(&all->list_envp, ft_lstnew(str, 0));
	else
		ft_lstadd_back(&all->list_envp, newlst_without_equal(str));
}

void	add_to_env(t_all *all, char *str, int status)
{
	t_env	*tmp;
	char	*s;

	s = get_newlst_name(str, 1, -1, 0);
	tmp = all->list_envp;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->name, s)))
		{
			if (status)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = get_newlst_name(str, 0, -1, 0);
			}
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_list(status, all, str);
	if (s)
		free(s);
}

void	export_print_error(char *str)
{
	ft_putstr_fd(ER_NAME": export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_status = 1;
}

void	builtin_export(t_all *all)
{
	int	i;
	int	equal;

	i = 0;
	if (!all->pipex->arg[1])
		print_sorted_env(all);
	else
	{
		if (all->pipe)
			return ;
		while (all->pipex->arg[++i] && !all->pipe)
		{
			equal = 1;
			if (check_line(all->pipex->arg[i]) == -1)
				export_print_error(all->pipex->arg[i]);
			else
			{
				if (check_line(all->pipex->arg[i]) == -2)
					equal = 0;
				add_to_env(all, all->pipex->arg[i], equal);
			}
		}
	}
}
