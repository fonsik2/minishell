/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_in.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:31:32 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/19 11:23:45 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_in_file(char *in_file, t_all *all)
{
	int		fd;
	char	*tmp;

	in_file = rename_file(in_file, all);
	if (!in_file)
		return (1);
	fd = open(in_file, O_RDONLY);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell : ", in_file);
		perror(tmp);
		free(tmp);
		free(in_file);
		g_exit = 1;
		return (1);
	}
	close(all->fd_in);
	all->fd_in = fd;
	free(in_file);
	return (0);
}

char	*redirect_in(char *str, int *i, t_all *all)
{
	char	*new_str;
	char	*in_file;
	int		index;
	int		start;

	index = *i;
	new_str = ft_substr(str, 0, index);
	index++;
	while (str[index] == ' ')
		index++;
	if (check_syntax_er(str, index))
		return (free_null(all, str, new_str));
	start = index;
	while (str[index] && str[index] != '>' && str[index] != '<'
		&& str[index] != '|' && str[index] != ' ')
		index++;
	in_file = ft_substr(str, start, index - start);
	if (open_in_file(in_file, all))
		return (free_null(all, str, new_str));
	*i = ft_strlen(new_str) - 1;
	if (str[index])
		new_str = write_end(&index, str, new_str);
	free(str);
	str = NULL;
	return (new_str);
}

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
