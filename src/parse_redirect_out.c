/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect_out.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:31:55 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:31:58 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_out_file(char *out_file, t_all *all)
{
	int		fd;
	char	*tmp;

	out_file = rename_file(out_file, all);
	if (!out_file)
		return (1);
	fd = open(out_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell : ", out_file);
		perror(tmp);
		free(tmp);
		free(out_file);
		g_exit_status = 1;
		return (1);
	}
	close(all->fd_out);
	all->fd_out = fd;
	free(out_file);
	return (0);
}

char	*redirect_out(char *str, int *i, t_all *all)
{
	char	*new_str;
	char	*out_file;
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
	out_file = ft_substr(str, start, index - start);
	if (open_out_file(out_file, all))
		return (free_null(all, str, new_str));
	*i = ft_strlen(new_str) - 1;
	if (str[index])
		new_str = write_end(&index, str, new_str);
	free(str);
	str = NULL;
	return (new_str);
}

static int	open_add_out_file(char *out_file, t_all *all)
{
	int		fd;
	char	*tmp;

	out_file = rename_file(out_file, all);
	if (!out_file)
		return (1);
	fd = open(out_file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		tmp = ft_strjoin("minishell : ", out_file);
		perror(tmp);
		free(tmp);
		free(out_file);
		g_exit_status = 1;
		return (1);
	}
	close(all->fd_add_out);
	all->fd_add_out = fd;
	free(out_file);
	return (0);
}

char	*redirect_out_add(char *str, int *i, t_all *all)
{
	char	*new_str;
	char	*out_file;
	int		index;
	int		start;

	index = *i;
	new_str = ft_substr(str, 0, index);
	index += 2;
	while (str[index] == ' ')
		index++;
	if (check_syntax_er(str, index))
		return (free_null(all, str, new_str));
	start = index;
	while (str[index] && str[index] != '>' && str[index] != '<'
		&& str[index] != '|' && str[index] != ' ')
		index++;
	out_file = ft_substr(str, start, index - start);
	if (open_add_out_file(out_file, all))
		return (free_null(all, str, new_str));
	*i = ft_strlen(new_str) - 1;
	if (str[index])
		new_str = write_end(&index, str, new_str);
	free(str);
	str = NULL;
	return (new_str);
}
