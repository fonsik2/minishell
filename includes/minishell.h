/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:22:06 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:22:42 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "libft.h"

# define NAME "minishell$"
# define ER_NAME "minishell"
# define GREEN "\x1b[3;32m"
# define END "\x1b[0m"

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_arg
{
	char			*str;
	struct s_arg	*next;
}	t_arg;

typedef struct s_pipe
{
	char			**arg;
	struct s_pipe	*next;
	int				pid;
	int				fd_in;
	int				fd_out;
	int				fd_add_out;
	int				pipe_id;
}	t_pipe;

typedef struct s_all
{
	t_env	*list_envp;
	char	**path;
	int		fd_in;
	int		fd_out;
	int		fd_add_out;
	int		tmp_in;
	int		pipe_fd_in;
	int		pipe_fd_out;
	char	*here_doc;
	int		pipe_id;
	int		pipe;
	t_arg	*arg_list;
	t_pipe	*pipex;
}	t_all;

int	g_exit_status; // global variable

// src && utils && exec
int		main(int argc, char **argv, char **envp);
int		envp_to_list(t_all *all, char **envp);
int		get_path(t_all *all, char *str);
void	slash(t_all *all);
int		get_name(t_env *new, char *str, int *i, char c);
void	write_arg_in_list(t_all *all, char *str);
t_arg	*argnew(char *s);
void	addback_argnew(t_arg **arg_list, t_arg *new);
void	handler_sig(void);
int		builtin(t_all *all);
int		len_str(char **str);
int		len_pipex(t_pipe *pipex);
int		len_env(t_env *env);
int		str_is_num(char *str);
void	close_fds(int fd_one, int fd_two, int fd_three);
char	*get_path_for_exec(t_all *all, char **new_arg);
char	**make_env(t_env *env, t_all *all);
int		init_fd_redirects(int fd_in, int fd_out, int fd_add_out);
void	handle_signals_in_proc(void);
int		init_pipe_for_fd(t_all *all);
void	exec_module(t_all *all);
void	exec_one(t_all *all);
void	exec_pipe(t_all *all);
void	exec_final(t_all *all);
void	init_fd_pipe(t_all *all, int fd_in, int fd_out);
char	*get_path_exec(t_all *all);
void	close_two_fds(int fd1, int fd2);
void	my_sigint(int signal);
void	close_five_fd(t_all *all);
void	my_sign_here(int i);
char	*free_null(t_all *all, char *str, char *new_str);

// builtin
void	builtin_echo(t_all *all, int i, int option, int fd);
void	builtin_exit(t_all *all);
void	builtin_pwd(t_all *all);
int		choose_fd(t_all *all);
void	builtin_cd(t_all *all);
int		check_after_cd_one(t_all *all, int *find);
int		check_after_cd_three(t_all *all, int *find, int flag);
int		ft_chdir(char *str, t_all *all);
void	add_new_pwd(t_all *all, char *old_pwd, char *pwd);
void	builtin_unset(t_all *all, int i);
void	builtin_export(t_all *all);
void	builtin_env(t_all *all, int fd);
t_env	*newlst_without_equal(char *str);
int		check_line(char *str);
void	print_sorted_env(t_all *all);
int		set_index(t_all *all);
void	export_print_error(char *str);

// libft
//void	ft_putstr_fd(char *s, int fd);
t_env	*ft_lstnew(char *str, int i);
int		ft_lstadd_back(t_env **lst, t_env *new);
//int		ft_strncmp(const char *s1, const char *s2, size_t n);
//int		ft_atoi(const char *str, int i);
//char	*ft_itoa(int n, int len); 
//char	**ft_split(char const *s, char c);
//int		ft_strcmp(const char *s1, const char *s2);
//char	*ft_strchr(const char *s, int c);
//char	*ft_strjoin(char *s1, char *s2, int n);
//int		ft_strlen(const char *str);
//char	*ft_strtrim(char *s1, char *set, int flag, size_t i);
//char	*ft_strdup(const char *s1);
//void	ft_bzero(void *s, size_t n);
//void	*ft_calloc(size_t count, size_t size);
//char	*ft_substr(char const *s, unsigned int start, size_t len);
//int		ft_isalnum(int c);
//int		ft_isdigit(int c);
//int		ft_isalpha(int c);
//char	*ft_strrchr(const char *s, int c);

// parser
void	parser(char *str, t_all *all);
char	*parse_space(char *str, int *i, t_all *all);
char	*parse_squote(char *str, int *i, t_all *all, int flag);
char	*parse_dquote(char *str, int *i, t_all *all, int flag);
char	*parse_dollar(char *str, int *i, t_all *all);
char	*is_dollar(char *str, t_all *all);
char	*parse_redirect(char *str, int *i, t_all *all);
int		find_token(char *str, int i);
char	*redirect_out(char *str, int *i, t_all *all);
char	*redirect_out_add(char *str, int *i, t_all *all);
char	*write_end(int *index, char *str, char *one);
char	*rename_file(char *out_file, t_all *all);
int		check_syntax_er(char *str, int index);
char	*redirect_in(char *str, int *i, t_all *all);
char	*parse_heredoc(char *str, int *i, t_all *all);
char	*parse_pipe(char *str, int *i, t_all *all);
void	list_arg_to_list_pipe(t_all *all);
t_pipe	*new_pipex(t_all *all, char **ar);
void	addback_pipex(t_pipe **pipex, t_pipe *new);
int		check_forbidden_symbols(char *str, int one, int two, int i);
int		check_closed_quote(int result);
int		check_empty_pipe(char *str, int i);

//free
void	free_all(t_all *all);
void	envp_list_free(t_all *all);
void	argv_list_free(t_all *all, int flag);
void	pipe_list_free(t_all *all);
void	ft_free(char **str);

void	rl_replace_line(const char *buffer, int val);

#endif
