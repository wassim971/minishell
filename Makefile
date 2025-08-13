# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 14:49:09 by wbaali            #+#    #+#              #
#    Updated: 2025/07/30 00:55:00 by ainthana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
LIBFT = libft/libft.a

SRC = \
	srcs/main.c \
	srcs/exec/cmd.c \
	srcs/env/env.c \
	srcs/parsing/expend.c srcs/parsing/expend1.c srcs/parsing/expend2.c srcs/parsing/get.c srcs/parsing/parsing.c \
	srcs/parsing/signal.c srcs/parsing/token.c \
	srcs/utils/free.c srcs/utils/free2.c srcs/utils/print.c srcs/utils/liste.c \
	srcs/utils/utils1.c srcs/utils/utils2.c srcs/utils/utils3.c srcs/utils/liste_utils.c srcs/utils/liste_utils2.c \
	srcs/builtins/builtins.c srcs/builtins/builtins1.c \

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
	@mkdir -p $(OBJ_DIR)/srcs/parsing $(OBJ_DIR)/srcs/exec $(OBJ_DIR)/srcs/builtin $(OBJ_DIR)/srcs/utils
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
