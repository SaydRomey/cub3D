# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 15:53:21 by cdumais           #+#    #+#              #
#    Updated: 2024/05/06 18:39:04 by cdumais          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# --------------------------------- VARIABLES -------------------------------- #
# **************************************************************************** #
NAME		:= cub3D
AUTHOR		:= cdumais & oroy

MAP			:= 	map/base/test.cub
MAPS_BONUS	:=	map/bonus/school.cub \
				map/bonus/castle.cub \
				map/bonus/water.cub \
				map/bonus/fire.cub \
				map/bonus/serpent.cub \
				map/bonus/kitchen.cub

IMG_DIR		:= img
INC_DIR		:= inc
LIB_DIR		:= lib
OBJ_DIR		:= obj
SRC_DIR		:= src
TMP_DIR		:= tmp

COMPILE		:= gcc
OPTIMIZE	:= -Ofast -flto
C_FLAGS		:= -Wall -Wextra -Werror $(OPTIMIZE)
# C_FLAGS		:= -Wall -Wextra -Werror -g
L_FLAGS		:=
HEADERS		:= -I$(INC_DIR)

REMOVE		:= rm -rf
NPD			:= --no-print-directory
VOID		:= /dev/null
OS			:= $(shell uname)
# **************************************************************************** #
# ---------------------------------- CONFIG  --------------------------------- #
# **************************************************************************** #
C_FLAGS		+= -DOS_MAC

GLFW_DIR	:= $(shell brew --prefix glfw)/lib
GLFW		:= -lglfw
FRAMEWORKS	:= -framework Cocoa -framework OpenGL -framework IOKit

L_FLAGS		:= $(L_FLAGS) -L$(GLFW_DIR) $(GLFW) $(FRAMEWORKS)

OPEN		:= open
MACHINE		:= $(shell uname -n)

SCREEN_W	:= 1920
SCREEN_H	:= 1080
C_FLAGS		+= -DWIDTH=$(SCREEN_W) -DHEIGHT=$(SCREEN_H)
# **************************************************************************** #
# -------------------------------- SUBMODULES -------------------------------- #
# **************************************************************************** #
INIT_CHECK	:= $(LIB_DIR)/.init_check
INIT		:= $(if $(wildcard $(INIT_CHECK)),,init_submodules)
# **************************************************************************** #
# --------------------------------- EVAL_PIC --------------------------------- #
# **************************************************************************** #
PIC_CHECK	:= ./$(IMG_DIR)/.pic_check
PIC			:= $(if $(wildcard $(PIC_CHECK)),,eval_pic)
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

L_FLAGS		:= $(L_FLAGS) -L$(MLX_BLD) -lmlx42
HEADERS		:= $(HEADERS) -I$(MLX_INC)
# **************************************************************************** #
# --------------------------------- H FILES ---------------------------------- #
# **************************************************************************** #
INC			:=	animations		draw			math_utils		raycast		   \
				asset			elevator		minimap			segworld	   \
				cleanup			error			parsing			utils		   \
				controls		levels			pixels			vfx			   \
				cub3d			map				player
# **************************************************************************** #
# --------------------------------- C FILES ---------------------------------- #
# **************************************************************************** #
SRC			:=	animation_utils				map_array						   \
				animation					map_list						   \
				assets_utils				map_utils						   \
				assets						map								   \
				cleanup						math_utils_circle				   \
				draw_circle					math_utils_triangle				   \
				draw_triangle				math_utils						   \
				draw						minimap_draw					   \
				elevator_buttons			minimap_utils					   \
				elevator_events				minimap							   \
				elevator_init				mouse							   \
				elevator_utils				parse_cubfile					   \
				error						parse_floor_ceiling				   \
				hooks						parse_map						   \
				info						parse_walls						   \
				level_change				pixel_color_utils				   \
				level_utils					pixel_colors					   \
				level						pixel_utils						   \
				main						pixels							   \
																			   \
				player_fov					radar_utils						   \
				player_movement_utils		radar							   \
				player_utils												   \
				player														   \
																			   \
				raycast_assets				segworld						   \
				raycast_dda					shadow							   \
				raycast_floor_draw			utils_img						   \
				raycast_floor				utils							   \
				raycast_init				validate_map					   \
				raycast_utils				validate_scene					   \
				raycast_walls				validate
# **************************************************************************** #
# -------------------------------- ALL FILES --------------------------------- #
# **************************************************************************** #
INCS		:=	$(addprefix $(INC_DIR)/, $(addsuffix .h, $(INC)))
SRCS		:=	$(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SRC)))
OBJS		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
# **************************************************************************** #
# -------------------------------- ALL * FILES ------------------------------- #
# **************************************************************************** #
# INCS		:=	$(wildcard $(INC_DIR)/*.h)
# SRCS		:=	$(wildcard $(SRC_DIR)/*.c)
# OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
# **************************************************************************** #
# ---------------------------------- RULES ----------------------------------- #
# **************************************************************************** #
all: $(INIT) $(PIC) $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJS) $(INCS)
	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@
	@echo "$$TITLE"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		$(CYAN)$(TIME)$(RESET)\n"

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
	@$(REMOVE) $(BONUS_CHECK) $(PIC_CHECK)
	@$(REMOVE) 

re: fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
# ---------------------------------- BONUS ----------------------------------- #
# **************************************************************************** #
BONUS_CHECK	:= ./.bonus

bonus: C_FLAGS += -DBONUS=1
bonus: re
bonus: $(BONUS_CHECK)

$(BONUS_CHECK):
	@if [ ! -f $(BONUS_CHECK) ]; then \
		echo "Switching to bonus build..."; \
		touch $(BONUS_CHECK); \
	else \
		echo "Bonus build is up to date."; \
	fi

.PHONY: bonus
# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
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
run: all
	$(eval ARG := $(if $(wildcard $(BONUS_CHECK)),$(MAPS_BONUS),$(MAP)))
	./$(NAME) $(ARG)

$(TMP_DIR):
	@mkdir -p $(TMP_DIR)

ffclean: fclean mlxclean
	@$(MAKE) fclean -C $(LIBFT_DIR) $(NPD)
	@$(REMOVE) $(TMP_DIR) $(INIT_CHECK)

.PHONY: run ffclean
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
'make fclean'  -> Removes $(NAME)
'make re'      -> Same as fclean and all
'make norm'    -> Runs 'norminette' on the files in $(SRC_DIR)/ and $(INC_DIR)/ (also in libft)
'make nm'      -> Checks symbols in the executable (to check used functions)
'make pdf'     -> Downloads/Opens a $(NAME) instruction pdf in $(TMP_DIR)/
'make mlxref'  -> Opens the MLX42 documentation
'make run'     -> Executes $(NAME) with pre-defined args
'make ffclean' -> Removes $(LIBFT), $(MLX) and the $(TMP_DIR)/ directory
'make zip'     -> Creates a compressed version of this project on the desktop
'make info'    -> Prints compilation information
'make title'   -> Prints an example version of the title
'make man'     -> Shows this message

endef
export MAN

man:
	@echo "$$MAN"

.PHONY: man
# **************************************************************************** #
# ----------------------------------- INFO ----------------------------------- #
# **************************************************************************** #
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
define TITLE
[$(BOLD)$(PURPLE)$@$(RESET)]\t\t$(GREEN)ready$(RESET)
$(PURPLE)
 _______  __   __  _______  _______  ______  
|:::::::||::| |::||:::::::||:::::::||::::::| 
|:::::::||::| |::||:|$(GREEN)▲$(PURPLE)|:::||:::::::||:::::::|
|:::::::||::|_|::||:::::::| ___|:::||:| |:::|
|:::::::||:::::::||::::::| |:::::::||:|_|:::|
|:::::|_ |:::::::||:|$(GREEN)▼$(PURPLE)|:::| ___|:::||:::::::|
|:::::::||:::::::||:::::::||:::::::||::::::| 
 ───────  ───────  ───────  ───────  ──────
$(RESET)

type 'make run' to execute
or   'make man' for more options

endef
export TITLE
# **************************************************************************** #
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
# **************************************************************************** #
# **************************************************************************** #
SGOINFRE 		:= ~/sgoinfre/photos_etudiants/*/*
PROFILE_PIC 	:= $(shell whoami).JPG
DESTINATION 	:= ./$(shell whoami)_profile_copy.JPG
PNG_DESTINATION := ./img/evaluator.png
PIC_RESIZE		:= 256

eval_pic: $(PIC_CHECK)

$(PIC_CHECK):
	@if [ ! -f $(PIC_CHECK) ]; then \
		FILE_PATH=$$(find $(SGOINFRE) -name $(PROFILE_PIC) | head -n 1); \
		if [ -z "$$FILE_PATH" ]; then \
			echo "$(RED)Error$(RESET): File $(YELLOW)$(PROFILE_PIC)$(RESET) not found."; \
		else \
			echo "$(GREEN)$(BOLD)Preparing $(ORANGE)$(NAME)$(RESET)"; \
			cp "$$FILE_PATH" $(DESTINATION); \
		fi; \
	fi
	@if [ ! -f $(PIC_CHECK) ]; then \
		sips -s format png $(DESTINATION) --out $(PNG_DESTINATION) > $(VOID) 2>&1; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Error$(RESET): Conversion failed."; \
		else \
			$(REMOVE) $(DESTINATION); \
		fi; \
	fi
	@if [ ! -f $(PIC_CHECK) ]; then \
		sips -Z $(PIC_RESIZE) $(PNG_DESTINATION) > $(VOID) 2>&1; \
		if [ $$? -ne 0 ]; then \
			echo "$(RED)Error$(RESET): Resizing failed."; \
		else \
			echo "$(GREEN):)$(RESET)"; \
		fi; \
	fi
	@touch $(PIC_CHECK)
# **************************************************************************** #
# ------------------------------- DEPENDENCIES  ------------------------------ #
# **************************************************************************** #
# **************************************************************************** # Homebrew
CHECK_BREW := $(shell command -v brew 2> /dev/null)

brew:
ifndef CHECK_BREW
	@echo "Installing Homebrew..."
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
else
	@echo "Homebrew is already installed, checking for updates..."
	@brew update
endif

delete_brew:
ifndef CHECK_BREW
	@echo "Homebrew not found"
else
	@echo "Removing Homebrew configuration lines from ~/.zshrc..."
	@sed -i '' \
		-e '/^# Load Homebrew Fix script/,/^source $$HOME\/.brewconfig.zsh/d' \
		~/.zshrc
	@echo "Homebrew configuration removed from ~/.zshrc."
	@echo "Deleting ~/.brewconfig.zsh file..."
	@rm -f ~/.brewconfig.zsh
	@echo "~/.brewconfig.zsh file deleted."
endif

brew_info:
	@open "https://docs.brew.sh/"
# 
# **************************************************************************** # CMake
CHECK_BREW := $(shell command -v brew 2> /dev/null)
CHECK_CMAKE := $(shell command -v cmake 2> /dev/null)

# Estimated time (based on when i installed it on my session)
ESTIMATED_TIME = "$(BOLD)7 min 15 seconds$(RESET)"

cmake:
ifndef CHECK_BREW
	@echo "Brew is needed to install CMake... run 'make brew' first."
else
  ifndef CHECK_CMAKE
	@echo "Installing CMake...this might take around $(ESTIMATED_TIME)..."
	@brew install cmake
  else
	@echo "CMake is already installed."
  endif
endif
# 
# **************************************************************************** # GLFW
CHECK_GLFW := $(shell command -v glfw 2> /dev/null)

# Estimated time (based on when i installed it on my session)
ESTIMATED_TIME = "$(BOLD)10 seconds$(RESET)"

glfw:
ifndef CHECK_BREW
	@echo "Brew is needed to install GLFW... run 'make brew' first."
else
  ifndef CHECK_GLFW
	@echo "Installing GLFW...this might take around $(ESTIMATED_TIME)"
	@brew install glfw
  else
	@echo "GLFW is already installed."
  endif
endif
# 
.PHONY: brew delete_brew brew_info cmake glfw
