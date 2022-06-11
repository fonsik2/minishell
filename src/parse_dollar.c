/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:00:56 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/30 12:30:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_env(t_all *all, char *two)
{
	t_env	*tmp;

	tmp = all->list_envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, two) == 0)
		{
			free(two);
			two = ft_strdup(tmp->value);
			return (two);
		}
		tmp = tmp->next;
	}
	free(two);
	return (NULL);
}

char	*write_end(int *index, char *str, char *one)
{
	char	*two;
	int		start;

	start = *index;
	while (str[*index])
		(*index)++;
	two = ft_substr(str, start, (*index) - start);
	if (!(one[0]))
		two = ft_strtrim(two, " ");
	one = ft_strjoin(one, two);
	free(two);
	return (one);
}

static char	*check_after_dollar(int *index, t_all *all, char *str, char *two)
{
	int	start;

	start = ++(*index);
	if (str[*index] == '?')
	{
		two = ft_itoa(g_exit_status);
		(*index)++;
	}
	else if (ft_isdigit(str[*index]))
	{
		two = ft_strdup("");
		(*index)++;
	}
	else if (str[*index] == '_' || ft_isalpha(str[*index]))
	{
		while (str[*index] == '_' || ft_isalnum(str[*index]))
			(*index)++;
		two = check_env(all, ft_substr(str, start, (*index) - start));
		if (!two)
			two = ft_strdup("");
	}
	if (!two)
		return (NULL);
	return (two);
}

char	*parse_dollar(char *str, int *i, t_all *all)
{
	char	*one;
	char	*two;
	int		index;

	index = *i;
	two = NULL;
	one = ft_substr(str, 0, index);
	two = check_after_dollar(&index, all, str, two);
	if (!two)
	{
		free(one);
		return (str);
	}
	(*i) += ft_strlen(two) - 1;
	one = ft_strjoin(one, two);
	free(two);
	if (str[index])
		one = write_end(&index, str, one);
	free(str);
	str = NULL;
	return (one);
}

char	*is_dollar(char *str, t_all *all)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ((str[i + 1] == '?')
				|| ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			str = parse_dollar(str, &i, all);
		i++;
	}
	return (str);
}
