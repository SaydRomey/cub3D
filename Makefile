# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/10 21:55:11 by cdumais           #+#    #+#              #
#    Updated: 2023/12/10 22:26:22 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# -------------------------------- VARIABLES --------------------------------- #
# **************************************************************************** #
NAME	:= cub3D
ARGS	:= 

INC_DIR	:= inc
LIB_DIR	:= lib
MLX_DIR := $(LIB_DIR)/minilibx
OBJ_DIR	:= obj
SRC_DIR	:= src
TMP_DIR	:= tmp

COMPILE	:= gcc
C_FLAGS	:= -Wall -Wextra -Werror
L_FLAGS	:= -L$(MLX_DIR) -lmlx
HEADERS	:= -I$(INC_DIR)

REMOVE	:= rm -rf
OS		:= $(shell uname -s)

ifeq ($(OS), Linux)
	MLX_DIR += /minilibx_linux
	L_FLAGS += -lbsd -lXext -lX11 -lm

else ifeq ($(OS), Darwin)
	MLX_DIR += /minilibx_macos
	L_FLAGS += -framework OpenGL -framework AppKit
else
	$(error Unsupported operating system: $(UNAME))
endif
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

$(NAME): $(OBJS)
	@$(COMPILE) $(C_FLAGS) $(OBJS) -o $@
	@echo "$@ is ready"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) | $(OBJ_DIR)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(REMOVE) $(OBJ_DIR)
	@echo "Object files removed"

fclean: clean
	@$(REMOVE) $(NAME)
	@echo "$(NAME) removed"

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
	@$(REMOVE) $(TMP_DIR)

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
