# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 21:55:11 by cdumais           #+#    #+#              #
#    Updated: 2023/12/12 15:53:44 by cdumais          ###   ########.fr        #
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
	L_FLAGS := -L$(MLX_DIR) -lmlx -lbsd -lXext -lX11 -lm
else ifeq ($(OS), Darwin)
	MLX_DIR := $(MLX_DIR)/minilibx_macos
	L_FLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
else
	$(error Unsupported operating system: $(UNAME))
endif

MLX			:= $(MLX_DIR)/libmlx.a
HEADERS		:= $(HEADERS) -I$(MLX_DIR)
# 
INIT_CHECK	:= $(LIB_DIR)/.init_check
INIT		:= $(if $(wildcard $(INIT_CHECK)),,init_submodules)
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
#TODO: fix the no message when "nothing to be done" should appear..
# all: init_submodules $(NAME)
all: $(INIT) $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(INCS) $(MLX)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@
	@echo "$(GREEN)$$TITLE$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) $(NPD)

$(MLX):
	@echo "Building minilibx in $(CYAN)$(UNDERLINE)$(MLX_DIR)$(RESET)..."
	@$(MAKE) -C $(MLX_DIR) > $(VOID) 2>&1 || \
		(echo "Failed to build minilibx in $(MLX_DIR)" && exit 1)
	@printf "$(UP)$(ERASE_LINE)"
	@echo "[$(BOLD)$(PURPLE)minilibx$(RESET)] \
	$(GREEN)\tbuilt successfully$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@echo "$(CYAN)Compiling...$(ORANGE)\t$(notdir $<)$(RESET)"
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@
	@printf "$(UP)$(ERASE_LINE)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(REMOVE) $(OBJ_DIR); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Object files removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No object files to remove$(RESET)"; \
	fi
	@$(MAKE) clean -C $(LIBFT_DIR) $(NPD)

fclean: clean
	@if [ -n "$(wildcard $(NAME))" ]; then \
		$(REMOVE) $(NAME); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(GREEN)Executable removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		$(YELLOW)No executable to remove$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
run: all
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

mlxclean:
	@if [ -f $(MLX) ]; then \
		make clean -C $(MLX_DIR) > $(VOID) 2>&1 || (echo "mlx clean error" \
			&& exit 1); \
		echo "[$(BOLD)$(PURPLE)minilibx$(RESET)] \
		$(GREEN)Library removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)minilibx$(RESET)] \
		$(YELLOW)No library to remove$(RESET)"; \
	fi

ffclean: fclean mlxclean
	@make fclean -C $(LIBFT_DIR) $(NPD)
	@$(REMOVE) $(TMP_DIR) $(INIT_CHECK)

.PHONY: run debug leaks assembly mlxclean ffclean
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
# **************************************************************************** #
init_submodules:
	@git submodule init
	@git submodule update
	@touch $(INIT_CHECK)
ifeq ($(OS), Linux)
	@chmod +x $(MLX_DIR)/configure
endif

.PHONY: init_submodules
# **************************************************************************** #
# ----------------------------------- DECO ----------------------------------- #
# **************************************************************************** #
define TITLE

$@ is ready

endef
export TITLE
# **************************************************************************** #
ESC			:= \033

RESET		:= $(ESC)[0m
BOLD		:= $(ESC)[1m
DIM			:= $(ESC)[2m
ITALIC		:= $(ESC)[3m
UNDERLINE	:= $(ESC)[4m
INVERT		:= $(ESC)[7m
HIDDEN		:= $(ESC)[8m
STRIKE		:= $(ESC)[9m

# Cursor movement
UP			:= $(ESC)[A
DOWN		:= $(ESC)[B
FORWARD		:= $(ESC)[C
BACK		:= $(ESC)[D
NEXT_LINE	:= $(ESC)[E
PREV_LINE	:= $(ESC)[F
COLUMN		:= $(ESC)[G
TOP_LEFT	:= $(ESC)[1;1H

# Erasing
ERASE_REST	:= $(ESC)[K
ERASE_LINE	:= $(ESC)[2K
ERASE_ALL	:= $(ESC)[2J
# **************************************************************************** #
# ---------------------------------- COLORS ---------------------------------- #
# **************************************************************************** #
# Text
BLACK		:= $(ESC)[30m
RED			:= $(ESC)[91m
GREEN		:= $(ESC)[32m
YELLOW		:= $(ESC)[93m
ORANGE		:= $(ESC)[38;5;208m
BLUE		:= $(ESC)[94m
PURPLE		:= $(ESC)[95m
CYAN		:= $(ESC)[96m
WHITE		:= $(ESC)[37m
GRAY		:= $(ESC)[90m

