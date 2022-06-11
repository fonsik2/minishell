# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smdyan <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/12 19:08:58 by smdyan            #+#    #+#              #
#    Updated: 2022/02/12 12:12:49 by smdyan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_isprint.c ft_putendl_fd.c ft_strlcat.c ft_substr.c ft_atoi.c ft_itoa.c\
	  ft_putnbr_fd.c ft_strlcpy.c ft_tolower.c ft_bzero.c ft_memchr.c\
	  ft_putstr_fd.c ft_strlen.c ft_toupper.c ft_calloc.c ft_memcmp.c\
	  ft_split.c ft_strmapi.c ft_isalnum.c ft_memcpy.c ft_strchr.c ft_strncmp.c\
	  ft_isalpha.c ft_memmove.c ft_strdup.c ft_strnstr.c ft_isascii.c\
	  ft_memset.c ft_striteri.c ft_strrchr.c ft_isdigit.c ft_putchar_fd.c\
	  ft_strjoin.c ft_strtrim.c\
	  ft_strequ.c ft_putendl.c ft_strcmp.c

OBJ = $(SRC:.c=.o)

INCLUDES = ./

HEADERS = libft.h

CC = gcc

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o : %.c Makefile
	$(CC) $(FLAGS) -c $< -o $@ -I$(INCLUDES) -MD

include $(wildcard *.d)

$(NAME): $(OBJ) 
	ar rc $(NAME) $?
	ranlib $(NAME)

clean:
	rm -f $(OBJ)
	rm -f $(wildcard *.d)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
