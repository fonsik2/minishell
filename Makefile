# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carys <carys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 17:30:39 by carys             #+#    #+#              #
#    Updated: 2022/06/15 18:59:22 by carys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCNAME	=	main.c					bin_echo_exit_pwd_env.c	ft_lstadd_back.c\
			envp_to_list.c			bin_cd_utils.c\
			exec.c					bin_builtin.c\
			exec_signal.c			bin_cd.c\
			exec_utils.c			bin_export.c\
			parse_redirect_out.c	bin_export_utils.c		utils_free.c\
			parse_space_redirect.c	bin_unset.c				utils.c\
			parse_dollar.c			parse_pipe.c			utils_list_new.c\
			parse_quote.c			parser.c				exec_one.c\
			parse_redirect_in.c		parse_utils.c			exec_final.c\
			parse_heredoc.c			parser_check.c			exec_utils_2.c

BLTDIR = ./MD/
SRCDIR = ./src/
HEADER	= ./includes
LIBFT = ./libft

SRCS = ${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS	=	${addprefix ${BLTDIR}, ${SRCNAME:%.c=%.o}}

LIBREADLN = /Users/carys/.brew/Cellar/readline/8.1.2/lib
HREADLN = /Users/carys/.brew/Cellar/readline/8.1.2/include

CC		=	cc
RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror

BGN		=	START
END	=	FINISH
CLR	=	\x1b[4;32m
RST		=	\x1b[0m

.PHONY:		all clean fclean re

all:		${BLTDIR} ${NAME}

$(BLTDIR):
	mkdir -p $(BLTDIR)

${BLTDIR}%.o: ${SRCDIR}%.c
			${CC} ${CFLAGS} -I${HEADER} -c $< -o $@ -MD

include $(wildcard *.d)

${NAME}:	${OBJS}
			make all -C ${LIBFT}
			${CC} ${CFLAGS} -g -L${LIBREADLN} -lreadline -L$(LIBFT) -lft\
				-I${HREADLN} -o ${NAME} ${OBJS}
			@printf "${CLR}${BGN}${RST}\n"

clean:
			${RM} ${BLTDIR}
			make fclean -C ${LIBFT}

fclean:		clean
			${RM} ${NAME}
			@printf "${CLR}${END}${RST}\n"

re:			fclean all

norm:
			@norminette ${SRCS} ${HEADER}
