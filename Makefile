# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 14:49:09 by wbaali            #+#    #+#              #
#    Updated: 2025/06/05 15:03:14 by wbaali           ###   ########.fr        #
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
	${CC} ${CFLAGS}${INCLUDE} -lreadline $^ -o $(NAME)

$(LIBFT) :
	$(MAKE) -C $(LIBFTPATH)

$(FT_PRINTF) : 
	$(MAKE) -C $(FT_PRINTF_PATH)

all: ${NAME}

clean:
	rm -f ${OBJS}
	$(MAKE) clean -C $(FT_PRINTF_PATH)
	$(MAKE) clean -C $(LIBFTPATH)

fclean: clean
	rm -f ${NAME}
	$(MAKE) fclean -C $(FT_PRINTF_PATH)
	$(MAKE) fclean -C $(LIBFTPATH)

re: fclean all

.PHONY: all clean fclean re
