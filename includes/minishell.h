/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:22:06 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/18 21:17:19 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <term.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>

# define NAME "our_minishell$"
# define ER_NAME "minishell"
# define YELLOW "\x1b[3;33m"
# define END "\x1b[0m"

typedef struct s_arg
{
	char			*str;
	struct s_arg	*next;
}	t_arg;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

typedef struct s_pipe
{
	char			**arg;
	int				pid;
	int				fd_in;
	int				fd_out;
	int				fd_add_out;
	int				pipe_id;
	struct s_pipe	*next;
}	t_pipe;

typedef struct s_all
{
	char	**envp;
	char	*here_doc;
	int		tmp_in;
	int		fd_in;
	int		fd_out;
	int		fd_add_out;
	int		pipe;
	int		pipe_id;
	int		pipe_fd_in;
	int		pipe_fd_out;
	t_arg	*arg_list;
	t_env	*list_envp;
	t_pipe	*pipex;
}	t_all;

int	g_exit;

//main
int		main(int argc, char **argv, char **envp);
void	handler_signal(void);
int		envp_to_list(t_all *all, char **envp);
t_env	*ft_lstnew(char *str, int i);
int		get_name(t_env *new, char *str, int *i, char c);

//free
void	ft_free(char **str);
void	free_all(t_all *all);
void	envp_list_free(t_all *all);
void	argv_list_free(t_all *all, int flag);
void	pipe_list_free(t_all *all);

//libft
//void	ft_putstr_fd(char *s, int fd);
//int	ft_strncmp(const char *s1, const char *s2, size_t n);
//int	ft_strcmp(const char *s1, const char *s2);
//int	ft_atoi(const char *str);
//char	*ft_itoa(int n);
//char	*ft_strtrim(char const *s1, char const *set);
//char	*ft_strchr(const char *s, int c);
//size_t ft_strlen(const char *s);
//char	*ft_substr(char const *s, unsigned int start, size_t len);
//char	*ft_strdup(const char *s1);
//char	*ft_strjoin(char const *s1, char const *s2);
//int	ft_isdigit(int c);
//int	ft_isdigit(int c);
//int	ft_isalnum(int c);
//char	**ft_split(char const *s, char c);
int		ft_lstadd_back(t_env **lst, t_env *new);

// parser
void	parser(char *str, t_all *all);
int		check_forbidden_symbols(char *str, int one, int two, int i);
int		check_closed_quote(int result);
int		check_empty_pipe(char *str, int i);
char	*parse_space(char *str, int *i, t_all *all);
void	write_arg_in_list(t_all *all, char *str);
char	*parse_squote(char *str, int *i, t_all *all, int flag);
char	*parse_dquote(char *str, int *i, t_all *all, int flag);
char	*is_dollar(char *str, t_all *all);
char	*parse_dollar(char *str, int *i, t_all *all);
char	*write_end(int *index, char *str, char *one);
char	*parse_redirect(char *str, int *i, t_all *all);
char	*redirect_out_add(char *str, int *i, t_all *all);
int		check_syntax_er(char *str, int index);
char	*free_null(t_all *all, char *str, char *new_str);
char	*rename_file(char *out_file, t_all *all);
char	*parse_heredoc(char *str, int *i, t_all *all);
char	*redirect_out(char *str, int *i, t_all *all);
char	*redirect_in(char *str, int *i, t_all *all);
char	*parse_pipe(char *str, int *i, t_all *all);
t_pipe	*new_pipex(t_all *all, char **ar);
void	addback_pipex(t_pipe **pipex, t_pipe *new);
void	list_arg_to_list_pipe(t_all *all);

//exec
int		len_pipex(t_pipe *pipex);
void	exec_one(t_all *all);
void	handle_signals_in_proc(void);
void	close_fds(int fd_one, int fd_two, int fd_three);
int		init_pipe_for_fd(t_all *all);
void	exec_final(t_all *all);
int		get_path(t_all *all, char *str);
void	slash(t_all *all);



int		len_env(t_env *env);
char	*get_path_for_exec(t_all *all, char **new_arg);
char	**make_env(t_env *env, t_all *all);
int		init_fd_redirects(int fd_in, int fd_out, int fd_add_out);
void	exec_module(t_all *all);

void	init_fd_pipe(t_all *all, int fd_in, int fd_out);
char	*get_path_exec(t_all *all);
void	my_sign_here(int i);

//builtin
int		builtin(t_all *all);
void	builtin_pwd(t_all *all);
int		choose_fd(t_all *all);

void	close_five_fd(t_all *all);
void	builtin_echo(t_all *all, int i, int option, int fd);
void	builtin_env(t_all *all, int fd);
void	builtin_export(t_all *all);
void	print_sorted_env(t_all *all);
void	close_two_fds(int fd1, int fd2);
int		check_line(char *str);
void	export_print_error(char *str);
void	builtin_unset(t_all *all, int i);
void	builtin_cd(t_all *all);
int		check_after_cd_one(t_all *all, int *find);
int		ft_chdir(char *str, t_all *all);
int		check_after_cd_three(t_all *all, int *find, int flag);
void	add_new_pwd(t_all *all, char *old_pwd, char *pwd);
void	builtin_exit(t_all *all);
int		len_str(char **str);
int		str_is_num(char *str);
t_env	*newlst_without_equal(char *str);

void	rl_replace_line(const char *buffer, int val);

#endif
