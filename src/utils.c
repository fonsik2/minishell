/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:34:24 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:34:30 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_str(char **str)
{
	int		len;
	char	**tmp;
	int		i;

	i = -1;
	len = 0;
	tmp = str;
	while (tmp[++i])
		len++;
	return (len);
}

int	str_is_num(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

void	close_fds(int fd_one, int fd_two, int fd_three)
{
	if (fd_one >= 0)
		close(fd_one);
	if (fd_two >= 0)
		close(fd_two);
	if (fd_three >= 0)
		close(fd_three);
}

int	len_pipex(t_pipe *pipex)
{
	t_pipe	*tmp;
	int		len;

	len = 0;
	tmp = pipex;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

int	len_env(t_env *env)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
