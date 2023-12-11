# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 21:55:11 by cdumais           #+#    #+#              #
#    Updated: 2023/12/11 16:46:25 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# -------------------------------- VARIABLES --------------------------------- #
# **************************************************************************** #
NAME		:= cub3D
ARGS		:= 

INC_DIR		:= inc
LIB_DIR		:= lib
OBJ_DIR		:= obj
SRC_DIR		:= src
TMP_DIR		:= tmp

COMPILE		:= gcc
C_FLAGS		:= -Wall -Wextra -Werror
# L_FLAGS		:= 
HEADERS		:= -I$(INC_DIR)

REMOVE		:= rm -rf
NPD			:= --no-print-directory
VOID		:= /dev/null
OS			:= $(shell uname -s)
# **************************************************************************** #
# ---------------------------------- LIBFT ----------------------------------- #
# **************************************************************************** #
LIBFT_DIR	:= $(LIB_DIR)/libft
LIBFT_INC	:= $(LIBFT_DIR)/$(INC_DIR)
LIBFT		:= $(LIBFT_DIR)/libft.a
HEADERS		:= $(HEADERS) -I$(LIBFT_INC)

# **************************************************************************** #
# -------------------------------- MINILIBX ---------------------------------- #
# **************************************************************************** #
MLX_DIR		:= $(LIB_DIR)/minilibx

ifeq ($(OS), Linux)
	MLX_DIR := $(MLX_DIR)/minilibx_linux
	L_FLAGS := -lmlx -lbsd -lXext -lX11 -lm
else ifeq ($(OS), Darwin)
	MLX_DIR := $(MLX_DIR)/minilibx_macos
	L_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error Unsupported operating system: $(UNAME))
endif

MLX			:= $(MLX_DIR)/libmlx.a
HEADERS		:= $(HEADERS) -I$(MLX_DIR)
# **************************************************************************** #
# -------------------------------- ALL * FILES ------------------------------- #
# **************************************************************************** #
INCS	:=	$(wildcard $(INC_DIR)/*.h)
SRCS	:=	$(wildcard $(SRC_DIR)/*.c)
OBJS	:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
# SRC		:=	
# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
# INC		:=
# **************************************************************************** #
# -------------------------------- ALL FILES --------------------------------- #
# **************************************************************************** #
# INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
# SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
# OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INCS) $(MLX)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@
	@echo "$@ is ready"

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX):
	@make -C $(MLX_DIR) > $(VOID) 2>&1 || \
		(echo "minilibx not found in $(MLX_DIR)" \
		&& exit 1)
	@echo "minilibx ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(REMOVE) $(OBJ_DIR); \
		echo "Object files removed"; \
	else \
		echo "No object files to remove"; \
	fi
	@make clean -C $(LIBFT_DIR) $(NPD)

# clean:
# 	@$(REMOVE) $(OBJ_DIR)
# 	@echo "Object files removed"
# 	@make clean -C $(LIBFT_DIR) $(NPD)

fclean: clean
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "$(NAME) removed"; \
	else \
		echo "No executable to remove"; \
	fi

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
run: $(NAME)
	./$(NAME) $(ARGS)

debug: C_FLAGS += -g
debug: re

leaks: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(ARGS)

assembly: $(NAME) | $(TMP_DIR)
	@$(COMPILE) $(C_FLAGS) -S $(SRCS) $(HEADERS)
	@mv *.s $(TMP_DIR)
	@echo "Assembly files created in $(TMP_DIR)"

$(TMP_DIR):
	@mkdir -p $(TMP_DIR)

ffclean: fclean
	@make fclean -C $(LIBFT_DIR) $(NPD)
	@$(REMOVE) $(TMP_DIR)
	@if [ -f $(MLX) ]; then \
		make clean -C $(MLX_DIR) > $(VOID) 2>&1 || \
			(echo "mlx clean error" \
			&& exit 1); \
		echo "$(MLX) removed"; \
	else \
		echo "no $(MLX) to remove"; \
	fi

.PHONY: run assembly ffclean
# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
PDF		:= cub3d_en.pdf
GIT_URL := https://github.com/SaydRomey/42_ressources
PDF_URL = $(GIT_URL)/blob/main/pdf/$(PDF)?raw=true

pdf: | $(TMP_DIR)
	@curl -# -L $(PDF_URL) -o $(TMP_DIR)/$(PDF)
ifeq ($(OS),Darwin)
	@open $(TMP_DIR)/$(PDF)
else
	@xdg-open $(TMP_DIR)/$(PDF) || echo "Please install a compatible PDF viewer"
endif

.PHONY: pdf
