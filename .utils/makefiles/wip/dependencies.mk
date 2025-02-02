
# **************************************************************************** #
# ------------------------------- DEPENDENCIES  ------------------------------ #
# **************************************************************************** #
# TODO: automate this...

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

# **************************************************************************** #
.PHONY: brew delete_brew brew_info cmake glfw
# **************************************************************************** #

# Dependencies for MLX42 for macOS

# HOMEBREW
# CMAKE
# GLFW


# # ideas to test
# GLFW_EXISTS	:= $(shell test -e $(GLFW_DIR)/libglfw.dylib && echo 1 || echo 0)
# GLFW		:= $(if $(filter $(GLFW_EXISTS),1),-lglfw, $(error GLFW library not found.)) #but install it instead ?

# GLFW_LIB_PATH=$(brew --prefix glfw)/lib
# if [ -e "$GLFW_LIB_PATH/libglfw.dylib" ]; then
# 	echo "-lglfw"
# else
# 	echo "GLFW library not found."
# fi

# 

# Dependencies for MLX42 for linux

# Cmake
# GLFW

# # this also works but i wanted to test stuff...
# GLFW		:= -glfw
# L_FLAGS		:= $(L_FLAGS) $(GLFW) $(LIBS)

# for the second monitor.. (gets the second line)
# SCREEN_W	:= $(shell $(XRANDR) | awk -Fx '{print $$1}' | head -n 2 | tail -n 1 || echo $(DEFAULT_W))
