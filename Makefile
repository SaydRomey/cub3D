# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/19 16:45:34 by cdumais           #+#    #+#              #
#    Updated: 2024/04/29 14:00:28 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TODO: check to install GLFW in lib dir like we did with readline ?
# or automate the installation of required dependencies (brew, cmake, glfw)

# https://lodev.org/cgtutor/raycasting.html

# https://doomwiki.org/wiki/Doom_rendering_engine

# https://pulgamecanica.herokuapp.com/posts/mlx42-intro

# assets:
# https://crusenho.itch.io/complete-gui-essential-pack


#TODO/TOCHECK:
# replace L_FLAGS by LDFLAGS:
# Extra flags to give to compilers when they are supposed to invoke the linker,
# 'ld', such as -L.
# Non-library linker flags, such as -L, should go in the LDFLAGS variable.
# Libraries (-lfoo) should be added to the LDLIBS variable instead.

# https://www.gnu.org/software/make/manual/make.html#Conditionals

# !** make a simple version of this makefile..

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
AUTHOR		:= cdumais & oroy
NAME		:= cub3D
MAP			:= map/test.cub
MAPS_BONUS	:= map/bonus/test.cub map/bonus/test1.cub map/bonus/test2.cub map/bonus/test3.cub

CFG_DIR		:= .cfg
IMG_DIR		:= img
INC_DIR		:= inc
LIB_DIR		:= lib
OBJ_DIR		:= obj
SRC_DIR		:= src
TMP_DIR		:= tmp
WAV_DIR		:= wav

COMPILE		:= gcc
C_FLAGS		:= -Wall -Wextra -Werror -Ofast -flto
# C_FLAGS		:= -Wall -Wextra -Werror -g
L_FLAGS		:= 
HEADERS		:= -I$(INC_DIR)

REMOVE		:= rm -rf
NPD			:= --no-print-directory
VOID		:= /dev/null
OS			:= $(shell uname)
# **************************************************************************** #
# ---------------------------------- LIBFT ----------------------------------- #
# **************************************************************************** #
LIBFT_DIR	:= $(LIB_DIR)/libft
LIBFT_INC	:= $(LIBFT_DIR)/$(INC_DIR)
LIBFT		:= $(LIBFT_DIR)/libft.a
HEADERS		:= $(HEADERS) -I$(LIBFT_INC)
# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
MLX_DIR		:= $(LIB_DIR)/MLX42
MLX_INC		:= $(MLX_DIR)/include/MLX42
MLX_BLD		:= $(MLX_DIR)/build
MLX42		:= $(MLX_BLD)/libmlx42.a

C_FLAGS		:= $(C_FLAGS) -Wunreachable-code -Ofast
L_FLAGS		:= $(L_FLAGS) -L$(MLX_BLD) -lmlx42
HEADERS		:= $(HEADERS) -I$(MLX_INC)
# **************************************************************************** #
# ---------------------------------- CONFIG  --------------------------------- #
# **************************************************************************** #
# TODO: adapt default to desired dimensions in config_*.mk
# TOCHECK: do we need more macros, and does the norm permit compile time defined macros ?
# 
ifeq ($(OS),Linux)
include $(CFG_DIR)/config_linux.mk
else ifeq ($(OS),Darwin)
include $(CFG_DIR)/config_mac.mk
else
$(error Unsupported operating system: $(OS))
endif

C_FLAGS		+= -DWIDTH=$(SCREEN_W) -DHEIGHT=$(SCREEN_H)
# **************************************************************************** #
# -------------------------------- SUBMODULES  ------------------------------- #
# **************************************************************************** #
INIT_CHECK	:= $(LIB_DIR)/.init_check
INIT		:= $(if $(wildcard $(INIT_CHECK)),,init_submodules)
# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
# INC		:= 
# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
# SRC		:=	
# **************************************************************************** #
# -------------------------------- ALL FILES --------------------------------- #
# **************************************************************************** #
# INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
# SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
# OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# -------------------------------- ALL * FILES ------------------------------- #
# **************************************************************************** #
INCS	:=	$(wildcard $(INC_DIR)/*.h)
SRCS	:=	$(wildcard $(SRC_DIR)/*.c)
OBJS	:=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(INIT) $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJS) $(INCS)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@
	@echo "$$TITLE"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) $(NPD)

$(MLX42):
	@echo "Building MLX42..."
	@cmake -S lib/MLX42 -B lib/MLX42/build -Wno-dev
	@echo "Compiling MLX42..."
	@$(MAKE) -C lib/MLX42/build -j4 $(NPD)
	@echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
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
	@$(REMOVE) $(BONUS_CHECK)

re: fclean all

# **************************************************************************** #
BONUS_CHECK	:= ./.bonus

# bonus:
# 	$(info Using C_FLAGS: $(C_FLAGS))
bonus: C_FLAGS += -DBONUS=1
bonus: re
bonus: $(BONUS_CHECK)
# print a different title..

$(BONUS_CHECK):
	@if [ ! -f $(BONUS_CHECK) ]; then \
		echo "Switching to bonus build..."; \
		touch $(BONUS_CHECK); \
	else \
		echo "Bonus build is up to date."; \
	fi

.PHONY: all clean fclean re bonus
# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
# TODO: add the option to recompile MLX with debug flag in this section...
# 
mlxclean:
	@if [ -f $(MLX42) ]; then \
		$(REMOVE) $(MLX_BLD); \
		echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
		$(GREEN)Library removed$(RESET)"; \
	else \
		echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
		$(YELLOW)No library to remove$(RESET)"; \
	fi

mlxref:
	@$(OPEN) "https://github.com/codam-coding-college/MLX42/tree/master/docs"

.PHONY: mlxclean mlxref
# **************************************************************************** #
# ----------------------------------- GIT ------------------------------------ #
# **************************************************************************** #
init_submodules: $(INIT_CHECK)

WHEN	:= $(shell date "+On day %d of month %m in the year %Y at %H:%M and %S seconds")

$(INIT_CHECK):
	@git submodule update --init --recursive
	@echo "$(NAME)\n\
	by $(AUTHOR)\n\
	Compiled for $(USER)\n\
	$(WHEN)\n\
	$(MACHINE)" > $@

MAIN_BRANCH	:= $(shell git branch -r \
| grep -E 'origin/(main|master)' \
| grep -v 'HEAD' | head -n 1 | sed 's@^.*origin/@@')

update:
	@echo "Are you sure you want to update the repo and submodules? [y/N] " \
	&& read ANSWER; \
	if [ "$$ANSWER" = "y" ] || [ "$$ANSWER" = "Y" ]; then \
		echo "Updating repository from branch $(CYAN)$(MAIN_BRANCH)$(RESET)..."; \
		git pull origin $(MAIN_BRANCH); \
		$(MAKE) init_submodules; \
		echo "Repository updated."; \
	else \
		echo "Canceling update..."; \
	fi

.PHONY: init_submodules update
# **************************************************************************** #
# ---------------------------------- NORME ----------------------------------- #
# **************************************************************************** #
norm:
	@if which norminette > $(VOID); then \
		echo "$(BOLD)$(YELLOW)Norminetting $(PURPLE)$(NAME)$(RESET)"; \
		norminette -o $(INCS); \
		norminette -o $(SRCS); \
		$(MAKE) norm -C $(LIBFT_DIR); \
	else \
		echo "$(BOLD)$(YELLOW)Norminette not installed$(RESET)"; \
	fi

nm: $(NAME)
	@echo "$(BOLD)$(YELLOW)Functions in $(PURPLE)$(UNDERLINE)$(NAME)$(RESET):"
	@nm $(NAME) | grep U | grep -v 'ft_' \
				| sed 's/U//g' | sed 's/__//g' | sed 's/ //g' \
				| sort | uniq
	@$(MAKE) nm -C $(LIBFT_DIR) $(NPD)

.PHONY: norm nm
# **************************************************************************** #
# ---------------------------------- PDF ------------------------------------- #
# **************************************************************************** #
PDF		:= cub3d_en.pdf
GIT_URL	:= https://github.com/SaydRomey/42_ressources
PDF_URL	:= $(GIT_URL)/blob/main/pdf/$(PDF)?raw=true

pdf: | $(TMP_DIR)
	@if [ -f $(TMP_DIR)/$(PDF) ]; then \
		echo "Opening $(PDF)..."; \
	else \
		echo "Downloading $(PDF)..."; \
		curl -# -L $(PDF_URL) -o $(TMP_DIR)/$(PDF); \
	fi
	@$(OPEN) $(TMP_DIR)/$(PDF)

.PHONY: pdf
# **************************************************************************** #
# ---------------------------------- UTILS ----------------------------------- #
# **************************************************************************** #
include $(CFG_DIR)/leaks.mk

# run: all
# 	./$(NAME) $(MAP)

run: all
	$(eval ARG := $(if $(wildcard $(BONUS_CHECK)),$(MAPS_BONUS),$(MAP)))
	./$(NAME) $(ARG)

run_bonus:
	./$(NAME) $(MAPS_BONUS)

FORCE_FLAGS	:= \
-Wno-unused-variable \
-Wno-unused-function

force: C_FLAGS += $(FORCE_FLAGS)
force: re
	@echo "adding flags $(YELLOW)$(FORCE_FLAGS)$(RESET)"
	@echo "$(RED)Forced compilation$(RESET)"
	./$(NAME) $(MAP)

$(TMP_DIR):
	@mkdir -p $(TMP_DIR)
# **************************************************************************** #
ffclean: fclean vclean mlxclean
	@$(MAKE) fclean -C $(LIBFT_DIR) $(NPD)
	@$(REMOVE) $(TMP_DIR) $(INIT_CHECK) $(NAME).dSYM

.PHONY: run debug force ffclean
# **************************************************************************** #
# ---------------------------------- BACKUP (zip) ---------------------------- #
# **************************************************************************** #
USER		:=$(shell whoami)
ROOT_DIR	:=$(notdir $(shell pwd))
TIMESTAMP	:=$(shell date "+%Y%m%d_%H%M%S")
BACKUP_NAME	:=$(ROOT_DIR)_$(USER)_$(TIMESTAMP).zip
MOVE_TO		:= ~/Desktop/$(BACKUP_NAME)

zip: ffclean
	@if which zip > $(VOID); then \
		zip -r --quiet $(BACKUP_NAME) ./*; \
		mv $(BACKUP_NAME) $(MOVE_TO); \
		echo "[$(BOLD)$(PURPLE)$(NAME)$(RESET)] \
		compressed as: $(CYAN)$(UNDERLINE)$(MOVE_TO)$(RESET)"; \
	else \
		echo "Please install zip to use the backup feature"; \
	fi

.PHONY: zip
# **************************************************************************** #
# ------------------------------------ MAN ----------------------------------- #
# **************************************************************************** #
define MAN

Available 'make' targets:

'make [all]'   -> Compiles $(NAME) and necessary dependencies (libft and MLX42)
'make clean'   -> Removes the $(OBJ_DIR)/ directory and other object files
'make fclean'  -> Removes $(NAME) and $(LIBFT)
'make re'      -> Same as fclean and all
'make update'  -> Pulls the github version
'make norm'    -> Runs 'norminette' on the files in $(SRC_DIR)/ and $(INC_DIR)/ (also in libft)
'make nm'      -> Checks symbols in the executable (to check used functions)
'make pdf'     -> Downloads/Opens a $(NAME) instruction pdf in $(TMP_DIR)/
'make mlxref'  -> Opens the MLX42 documentation
'make leaks'   -> (WIP) Runs Valgrind on $(NAME) $(MAP) (make supp and make suppleaks)
'make run'     -> Same as 'make all', then './$(NAME) $(MAP)'
'make debug'   -> (WIP) Recompiles with debug symbols
'make force'   -> Recompiles with $(YELLOW)$(FORCE_FLAGS)$(RESET) (for testing)
'make ffclean' -> Removes files and directories created by this makefile
'make zip'     -> Creates a compressed version of this project on the desktop
'make info'    -> Prints compilation information
'make title'   -> Prints an example version of the title
'make spin'    -> (WIP) Animation that waits for a process to finish
'make sound'   -> (WIP) Plays a .wav sound
'make man'     -> Shows this message

endef
export MAN

man:
	@echo "$$MAN"

.PHONY: man
# **************************************************************************** #
# ----------------------------------- INFO ----------------------------------- #
# **************************************************************************** #
# This is only to make sure the compilation gets everything
# 
define INFO

$(NAME)
by $(AUTHOR)


$(UNDERLINE)Compiler$(RESET)
$(COMPILE)

$(UNDERLINE)C_FLAGS$(RESET)
 $(C_FLAGS)

$(UNDERLINE)I_FLAGS$(RESET)
$(HEADERS)

$(UNDERLINE)L_FLAGS$(RESET)
$(L_FLAGS)

$(UNDERLINE)Header files$(RESET)
$(INCS)

$(UNDERLINE)Source code$(RESET)
$(SRCS)

$(UNDERLINE)Libraries$(RESET)
$(LIBFT) $(MLX42)

$(UNDERLINE)Screen resolution$(RESET)
Width: $(SCREEN_W)
Height:$(SCREEN_H)

endef
export INFO

info:
	@echo "$$INFO"

.PHONY: info
# **************************************************************************** #
# ----------------------------------- DECO ----------------------------------- #
# **************************************************************************** #
# TODO: better title (ASCII ART?)
# 
define TITLE
[$(BOLD)$(PURPLE)$@$(RESET)]\t\t$(GREEN)ready$(RESET)
$(ORANGE)
***************
* PLACEHOLDER *
***************
$(RESET)

type 'make run' to execute
or   'make man' for more options

endef
export TITLE

define TITLE_BONUS
[$(BOLD)$(PURPLE)$@$(RESET)]\t\t$(GREEN)ready$(RESET)
$(ORANGE)
***************
* PLACEHOLDER *
**** BONUS ****
***************
$(RESET)

type 'make run' to execute
or   'make man' for more options

endef
export TITLE_BONUS

USER		:=$(shell whoami)
TIME		:=$(shell date "+%H:%M:%S")

title:
	@echo "$$TITLE"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"

.PHONY: title
# **************************************************************************** #
# ----------------------------------- ANSI ----------------------------------- #
# **************************************************************************** #
ESC			:= \033

RESET		:= $(ESC)[0m
BOLD		:= $(ESC)[1m
ITALIC		:= $(ESC)[3m
UNDERLINE	:= $(ESC)[4m

# Cursor movement
UP			:= $(ESC)[A
DOWN		:= $(ESC)[B
TOP_LEFT	:= $(ESC)[1;1H

# Erasing
ERASE_REST	:= $(ESC)[K
ERASE_LINE	:= $(ESC)[2K
ERASE_ALL	:= $(ESC)[2J

# Text color
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

# Background
BG_BLACK	:= $(ESC)[40m
BG_RED		:= $(ESC)[101m
BG_GREEN	:= $(ESC)[102m
BG_YELLOW	:= $(ESC)[103m
BG_ORANGE	:= $(ESC)[48;5;208m
BG_BLUE		:= $(ESC)[104m
BG_PURPLE	:= $(ESC)[105m
BG_CYAN		:= $(ESC)[106m
BG_WHITE	:= $(ESC)[47m
BG_GRAY		:= $(ESC)[100m
# **************************************************************************** #
# ------------------------------- ANIMATIONS --------------------------------- #
# **************************************************************************** #
# TODO: add a chmod + x to the script
# TODO: set this up during mlx42's compilation? or when installing brew, cmake, glfw
# 
# Animation shell script
SPIN_SH		:= $(CFG_DIR)/spinner.sh

# Message to display alongside the animation
SPIN_MSG	:= "Simulating compilation and linking for five seconds..."

# Create the file to stop the spinner (will be replaced by libmlx.a or something)
SPIN_FILE	:= "$(CFG_DIR)/.tmptestfile"

# spin time to stimulate duration (will be replaced by an other process)
PROCESS		:= sleep 5

spin:
	@$(REMOVE) $(SPIN_FILE)
	@echo "$(BOLD)$(PURPLE)Starting a long running task...$(RESET)"
	@$(SPIN_SH) $(SPIN_MSG) $(SPIN_FILE) &
	@$(PROCESS)
	@touch $(SPIN_FILE)
	@sleep 0.2
	@printf "$(UP)$(ERASE_LINE)"
	@echo "$(BOLD)$(GREEN)Long-running task completed.$(RESET)"
	@$(MAKE) spin2 $(NPD)


SPIN_MSG2	:= "Simulating something else for three seconds..."
PROCESS2	:= sleep 3

spin2:
	@$(REMOVE) $(SPIN_FILE)
	@echo "$(BOLD)$(PURPLE)Starting a shorter running task...$(RESET)"
	@$(SPIN_SH) $(SPIN_MSG2) $(SPIN_FILE) &
	@$(PROCESS2)
	@touch $(SPIN_FILE)
	@sleep 0.2
	@printf "$(UP)$(ERASE_LINE)"
	@echo "$(BOLD)$(GREEN)shorter task completed.$(RESET)"

.PHONY: spin spin2
# **************************************************************************** #
# --------------------------------- SOUNDS ----------------------------------- #
# **************************************************************************** #
# https://sound-effects.bbcrewind.co.uk/
# https://soundbible.com/
# or convert youtube/mp3/etc. to .wav
# 
WAV_DESTROY	:= $(WAV_DIR)/destroy.wav

sound:
	@echo "testing a .wav sound"
	@$(SOUND) $(WAV_DESTROY)
	@echo "sound testing finished"

.PHONY: sound
# **************************************************************************** #

# TOCHECK: using evaluator image in sgoinfre
# (mac only)
# find ~/sgoinfre -name "$(whoami).JPG" -exec sh -c 'sips -s format png "$0" --out "$(pwd)/img/$(basename "$0" .JPG).png"' {} \;

SGOINFRE	:= ~/sgoinfre/photos_etudiants/*/*
PROFILE_PIC	:= $(shell whoami).JPG
PICTURE		:= ./$(IMG_DIR)/username.png
# PICTURE		:= ./$(IMG_DIR)/$(PROFILE_PIC:.JPG=.png)

user_picture:
	@echo "searching for $(PROFILE_PIC) in $(SGOINFRE)..."
	@FILE_PATH=$$(find $(SGOINFRE) -name $(PROFILE_PIC)); \
	if [ -z "$$FILE_PATH" ]; then \
		echo "Error: File $(PROFILE_PIC) not found in $(SGOINFRE)."; \
		exit 1; \
	else \
		echo "Found file at $$FILE_PATH"; \
	fi
	@echo "Converting $$FILE_PATH to PNG..."
	@sips -s format png "$$FILE_PATH" --out $(PICTURE); \
	if [$$? -ne 0 ]; then \
		echo "Error: Conversion failed."; \
		exit 1; \
	else \
		echo "Conversion successful. File saved to $(PICTURE)"; \
	fi

convert:
	@sips -s format png "./misc/$(shell whoami).JPG" --out generic.png

# maybe change the file name to a generic one, to be called in cub3D ..?

.PHONY: user_picture
