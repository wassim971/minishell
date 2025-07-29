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
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LIBFT = libft/libft.a

SRC = \
	srcs/main.c \
	srcs/cmd.c srcs/env.c srcs/expend.c srcs/expend1.c srcs/expend2.c srcs/free.c srcs/free2.c \
	srcs/get.c srcs/liste.c srcs/liste_utils.c srcs/liste_utils2.c srcs/parsing.c srcs/print.c \
	srcs/signal.c srcs/token.c srcs/utils1.c srcs/utils2.c srcs/utils3.c \

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# ───── Colors ─────
RESET = \033[0m
BOLD = \033[1m
OK = \033[32m✔
FAIL = \033[31m✘
ACT = \033[36m➤
INFO = \033[34m•

all: $(OBJ_DIR) $(LIBFT) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/srcs
	@echo "$(ACT) Dossiers objets prêts."

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "$(OK) $(NAME) compilé avec succès.$(RESET)"

$(LIBFT):
	@echo "$(ACT) Compilation libft..."
	@$(MAKE) --no-print-directory -C libft > /dev/null

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Ilibft -c $< -o $@
	@echo "$(INFO) Compilation : $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C libft clean > /dev/null
	@echo "$(FAIL) Fichiers objets nettoyés.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C libft fclean > /dev/null
	@echo "$(FAIL) Exécutable supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
