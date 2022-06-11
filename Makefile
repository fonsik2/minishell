# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 17:19:33 by smdyan            #+#    #+#              #
#    Updated: 2022/06/11 17:21:17 by smdyan           ###   ########.fr        #
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

BLTDIR = ./built/
SRCDIR = ./src/
SRCS = ${addprefix ${SRCDIR}, ${SRCNAME}}
OBJS	=	${addprefix ${BLTDIR}, ${SRCNAME:%.c=%.o}}

HEADER	=	./includes

LIBREADLN = /usr/local/Cellar/readline/8.1.2/lib/
HREADLN = /usr/local/Cellar/readline/8.1.2/include
LIBFT = ./libft

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

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
			
clean:
			rm -rf ${BLTDIR}
			make fclean -C ${LIBFT}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
