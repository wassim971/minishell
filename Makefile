# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wassim <wassim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 14:49:09 by wbaali            #+#    #+#              #
#    Updated: 2025/06/08 14:19:19 by wassim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =  $(addprefix srcs/, main.c)

SRCS = ${SRC}

OBJS = ${SRCS:.c=.o}

INCLUDE = -Iinc

CC = cc

CFLAGS = -Wall -Werror -Wextra

LIBFTPATH = libft

LIBFT = $(LIBFTPATH)/libft.a

.c.o:
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o} 

$(NAME) : $(OBJS) $(LIBFT)
	${CC} ${CFLAGS} ${INCLUDE} $^ -lreadline -no-pie -o $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFTPATH)

$(FT_PRINTF) : 
	$(MAKE) -C $(FT_PRINTF_PATH)

all: ${NAME}

clean:
	rm -f ${OBJS}
	$(MAKE) clean $(FT_PRINTF_PATH)
	$(MAKE) clean $(LIBFTPATH)

fclean: clean
	rm -f ${NAME}
	$(MAKE) fclean $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re
