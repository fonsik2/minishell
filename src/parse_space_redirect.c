/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space_redirect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ephantom <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 13:01:54 by ephantom          #+#    #+#             */
/*   Updated: 2022/03/30 12:30:28 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_space(char *str, int *i, t_all *all)
{
	char	*new_str;
	int		index;

	index = *i;
	new_str = ft_substr(str, 0, index);
	index++;
	if (ft_strlen(new_str))
		write_arg_in_list(all, new_str);
	free(new_str);
	new_str = NULL;
	while (str[index] == ' ')
		index++;
	new_str = ft_substr(str, index, ft_strlen(str) - index);
	(*i) = -1;
	free(str);
	str = NULL;
	return (new_str);
}

char	*parse_redirect(char *str, int *i, t_all *all)
{
	if (str[*i] == '>' && str[*i + 1] == '>')
		str = redirect_out_add(str, i, all);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		str = parse_heredoc(str, i, all);
	else if (str[*i] == '>')
		str = redirect_out(str, i, all);
	else if (str[*i] == '<')
		str = redirect_in(str, i, all);
	return (str);
}
