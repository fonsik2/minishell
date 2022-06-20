# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carys <carys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/15 17:30:39 by carys             #+#    #+#              #
#    Updated: 2022/06/20 20:37:07 by carys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCNAME	=	main.c				parser.c			bin_builtin.c\
			envp_to_list.c		parse_dollar.c		bin_echo_exit_pwd_env.c\
			utils.c				parse_pipe.c		bin_cd.c\
			utils_free.c		parse_quote.c		bin_cd_utils.c\
			utils_list_new.c	parser_check.c		bin_export.c\
			exec.c				parse_utils.c		bin_export_utils.c\
			exec_utils.c		parse_heredoc.c		bin_unset.c\
			exec_signal.c		parse_redirect_out.c\
			exec_one_final.c	parse_redirect_in_space.c\

BLTDIR = ./MD/
SRCDIR = ./src/
HEADER = ./includes
LIBFT = ./libft
LIBFT_LIB	= $(LIBFT)/libft.a

SRCS 	= ${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS	= ${addprefix ${BLTDIR}, ${SRCNAME:%.c=%.o}}

LIBREADLN = /Users/carys/.brew/Cellar/readline/8.1.2/lib
HREADLN = /Users/carys/.brew/Cellar/readline/8.1.2/include

CC		=	cc
RM		=	rm -rf

CFLAGS	=	-Wall -Wextra -Werror

BGN		=	START
END		=	FINISH
CLR		=	\x1b[4;33m
RST		=	\x1b[0m

.PHONY:		all clean fclean re make_lib

all:		${BLTDIR} ${NAME}

$(BLTDIR):
	mkdir -p $(BLTDIR)

${BLTDIR}%.o: ${SRCDIR}%.c
			${CC} ${CFLAGS} -g -I${HEADER} -MD -c $< -o $@

include $(wildcard *.d)
include $(wildcard MD/*.d)
include $(wildcard src/*.d)

${NAME}:	${OBJS} $(LIBFT_LIB)
			${CC} ${CFLAGS} -L${LIBREADLN} -lreadline -L${LIBFT} -lft\
				-I${HREADLN} -o ${NAME} ${OBJS}
			@printf "${CLR}${BGN}${RST}\n"

$(LIBFT_LIB):	make_lib ;

make_lib:
			@${MAKE} -C $(LIBFT)

clean:
			${RM} ${BLTDIR}
			${MAKE} clean -C ${LIBFT}

fclean:		clean
			${RM} ${NAME}
			${MAKE} fclean -C ${LIBFT}
			@printf "${CLR}${END}${RST}\n"

re:			fclean all

norm:
			@norminette ${SRCS} ${HEADER} ${LIBFT}
