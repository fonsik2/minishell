/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:01:18 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/30 12:30:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_squote(int *index, char *str, char *one, char c)
{
	char	*two;
	int		start;

	start = ++(*index);
	while (str[*index] != c)
		(*index)++;
	two = ft_substr(str, start, (*index) - start);
	one = ft_strjoin(one, two);
	free(two);
	return (one);
}

char	*parse_squote(char *str, int *i, t_all *all, int flag)
{
	char	*new_str;
	char	*empty;
	int		index;

	index = *i;
	new_str = find_squote(&index, str, ft_substr(str, 0, index), '\'');
	(*i) = ft_strlen(new_str) - 1;
	if (flag == 1)
	{
		if (!new_str[0] && (str[index + 1] == ' ' || str[index + 1] == '\0'))
		{
			empty = ft_strdup("");
			write_arg_in_list(all, empty);
			free(empty);
		}
	}
	if (str[index + 1])
		new_str = find_squote(&index, str, new_str, '\0');
	free(str);
	str = NULL;
	return (new_str);
}

static char	*write_end_dquote(int *index, char *str, char *one)
{
	char	*two;
	int		start;

	start = ++(*index);
	while (str[*index])
		(*index)++;
	two = ft_substr(str, start, (*index) - start);
	one = ft_strjoin(one, two);
	free(two);
	return (one);
}

static void	have_flag(t_all *all, char *one, char *str, int index)
{
	char	*empty;

	if (!one[0] && (str[index + 1] == ' ' || str[index + 1] == '\0'))
	{
		empty = ft_strdup("");
		write_arg_in_list(all, empty);
		free(empty);
	}
}

char	*parse_dquote(char *str, int *i, t_all *all, int flag)
{
	char	*one;
	char	*two;
	int		index;
	int		start;

	index = *i;
	one = ft_substr(str, 0, index);
	start = ++index;
	while (str[index] != '"')
		index++;
	two = ft_substr(str, start, index - start);
	if (ft_strchr(two, '$'))
		two = is_dollar(two, all);
	one = ft_strjoin(one, two);
	free(two);
	(*i) = ft_strlen(one) - 1;
	if (flag == 1)
		have_flag(all, one, str, index);
	if (str[index + 1])
		one = write_end_dquote(&index, str, one);
	free(str);
	str = NULL;
	return (one);
}
