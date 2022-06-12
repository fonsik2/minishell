/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:30:16 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:30:19 by smdyan           ###   ########.fr       */
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
	char	*tmp;
	int		start;

	start = *index;
	while (str[*index])
		(*index)++;
	two = ft_substr(str, start, (*index) - start);
	if (!(one[0]))
	{
		tmp = two;
		two = ft_strtrim(tmp, " ");
		free(tmp);
	}
	tmp = ft_strjoin(one, two);
	free(two);
	free(one);
	return (tmp);
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
	char	*tmp;
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
	tmp = ft_strjoin(one, two);
	free(two);
	free(one);
	if (str[index])
		tmp = write_end(&index, str, tmp);
	free(str);
	str = NULL;
	return (tmp);
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
