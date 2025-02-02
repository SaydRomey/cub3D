
# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
MLX_DIR		:= $(LIB_DIR)/MLX42
MLX_INC		:= $(MLX_DIR)/include/MLX42
MLX_BLD		:= $(MLX_DIR)/build
MLX42		:= $(MLX_BLD)/libmlx42.a

L_FLAGS		:= $(L_FLAGS) -L$(MLX_BLD) -lmlx42
HEADERS		:= $(HEADERS) -I$(MLX_INC)

# OS			:= $(shell uname) # in utils.mk

ifeq ($(OS), Linux)
	C_FLAGS		+= -DOS_LINUX
	GLFW_DIR 	:= $(shell ldconfig -p | grep libglfw | awk '{print $$4}' | xargs dirname | uniq)
	GLFW		:= $(shell pkg-config --libs glfw3)
	LIBS		:= -ldl -lm -pthread
	L_FLAGS		:= $(L_FLAGS) -L$(GLFW_DIR) $(GLFW) $(LIBS)
	DEFAULT_W	:= 500
	DEFAULT_H	:= 500
	XRANDR		:= xrandr | grep '*' | awk '{print $$1}'
	SCREEN_W	:= $(shell $(XRANDR) | awk -Fx '{print $$1}' | head -n 1 || echo $(DEFAULT_W))
	SCREEN_H	:= $(shell $(XRANDR) | awk -Fx '{print $$2}' | head -n 1 || echo $(DEFAULT_H))
else ifeq ($(OS), Darwin)
	C_FLAGS		+= -DOS_MAC
	GLFW_DIR	:= $(shell brew --prefix glfw)/lib
	GLFW		:= -lglfw
	FRAMEWORKS	:= -framework Cocoa -framework OpenGL -framework IOKit
	L_FLAGS		:= $(L_FLAGS) -L$(GLFW_DIR) $(GLFW) $(FRAMEWORKS)
	DEFAULT_W	:= 1920
	DEFAULT_H	:= 1080
	OSA_SCREEN	:= osascript -e 'tell application "Finder" to get bounds of window of desktop'
	SCREEN_W	:= $(shell $(OSA_SCREEN) | awk '{gsub(/,/, "", $$3); print $$3}' || echo $(DEFAULT_W))
	SCREEN_H	:= $(shell $(OSA_SCREEN) | awk '{gsub(/,/, "", $$4); print $$4}' || echo $(DEFAULT_H))
else
$(error Unsupported operating system: $(OS))
endif

# C_FLAGS		+= -DSCREEN_WIDTH=$(SCREEN_W) -DSCREEN_HEIGHT=$(SCREEN_H)
# **************************************************************************** #
# -------------------------------- SUBMODULES  ------------------------------- #
# **************************************************************************** #
# in git.mk maybe ?
# INIT_CHECK	:= $(LIB_DIR)/.init_check
# INIT		:= $(if $(wildcard $(INIT_CHECK)),,init_submodules)

# 

# all: $(INIT) $(NAME)

# $(NAME): $(MLX42) $(LIBFT) $(OBJS) $(INCS)
# 	@$(COMPILE) $(C_FLAGS) $(HEADERS) $(OBJS) $(LIBFT) $(L_FLAGS) -o $@

# $(MLX42):
# 	@echo "Building MLX42..."
# 	@cmake -S lib/MLX42 -B lib/MLX42/build -Wno-dev
# 	@echo "Compiling MLX42..."
# 	@$(MAKE) -C lib/MLX42/build -j4 $(NPD)

# **************************************************************************** #
# ----------------------------------- MLX ------------------------------------ #
# **************************************************************************** #
# TODO: add the option to recompile MLX with debug flag in this section...
# 
# mlxclean:
# 	@if [ -f $(MLX42) ]; then \
# 		$(REMOVE) $(MLX_BLD); \
# 		echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
# 		$(GREEN)Library removed$(RESET)"; \
# 	else \
# 		echo "[$(BOLD)$(PURPLE)MLX42$(RESET)] \
# 		$(YELLOW)No library to remove$(RESET)"; \
# 	fi

# mlxref:
# 	@$(OPEN) "https://github.com/codam-coding-college/MLX42/tree/master/docs"

# .PHONY: mlxclean mlxref
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