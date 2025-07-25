# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 14:49:09 by wbaali            #+#    #+#              #
#    Updated: 2025/07/18 02:51:27 by wbaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =  $(addprefix srcs/, main.c cmd.c env.c expend.c expend1.c expend2.c free.c free2.c get.c liste_utils.c liste_utils2.c liste.c parsing.c print.c signal.c token.c utils1.c utils2.c utils3.c)

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
