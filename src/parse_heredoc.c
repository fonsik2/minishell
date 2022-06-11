/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:30:35 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:30:39 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc(char *limiter, int fd)
{
	char	*here;

	here = ft_strdup("");
	if (!limiter || !here)
		exit(EXIT_FAILURE);
	signal(SIGINT, my_sign_here);
	while (ft_strcmp(here, limiter))
	{
		free(here);
		here = readline("> ");
		if (!here)
			break ;
		if (ft_strcmp(here, limiter))
		{
			write(fd, here, ft_strlen(here));
			write(fd, "\n", 1);
		}
	}
	free(limiter);
	if (here)
		free(here);
	exit(EXIT_SUCCESS);
}

static int	er_print(char *str, char *limiter)
{
	perror(str);
	free(limiter);
	g_exit_status = 1;
	return (g_exit_status);
}

static int	read_heredoc(char *limiter, t_all *all)
{
	int	fd;
	int	pid;
	int	status;

	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (er_print(ER_NAME" : here_doc ", limiter));
	all->here_doc = ft_strjoin(getcwd(NULL, 0), "/here_doc");
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
		return (er_print(ER_NAME" : ", limiter));
	if (pid == 0)
		return (ft_heredoc(limiter, fd));
	wait(&status);
	g_exit_status = WEXITSTATUS(status);
	close(fd);
	free(limiter);
	return (g_exit_status);
}

static char	*get_new_str(char *new_str, char *str, int *index)
{
	new_str = ft_strjoin(new_str, "< here_doc ");
	if (str[*index])
		new_str = write_end(index, str, new_str);
	return (new_str);
}

char	*parse_heredoc(char *str, int *i, t_all *all)
{
	char	*new_str;
	char	*limiter;
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
	limiter = ft_substr(str, start, index - start);
	if (read_heredoc(limiter, all))
		return (free_null(all, str, new_str));
	handler_sig();
	(*i) = ft_strlen(new_str) - 1;
	new_str = get_new_str(new_str, str, &index);
	free(str);
	str = NULL;
	return (new_str);
}
