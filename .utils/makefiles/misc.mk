
# ==============================
##@ 🎨 Decorations
# ==============================

define PROJECT_TITLE

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

endef
export PROJECT_TITLE

title: ## Print ft_irc's logo in ASCII art
	@echo "$(BOLD)$(PURPLE)$(NAME)$(GREEN) created$(RESET)"
	@echo "$(GREEN)$$PROJECT_TITLE$(RESET)"
	@echo "Created by $(BOLD)$(TEAM)$(RESET)"
	@echo "Feat $(BLUE)$(COLLAB)$(RESET)"
	@echo "Compiled for $(ITALIC)$(BOLD)$(PURPLE)$(USER)$(RESET) \
		\t$(CYAN)$(TIME)$(RESET)\n"

.PHONY: title

# ==============================
##@ 🔈 Sound
# ==============================

# Sound Files
WAV_DIR		:= ./utils/wav
WAV_WELCOME	:= $(WAV_DIR)/welcome.wav
WAV_PUSHIT	:= $(WAV_DIR)/push.wav

pushit: ## push it to the limit
	@$(PLAY_SOUND) $(WAV_PUSHIT)

welcome: ## what can i say
	@$(PLAY_SOUND) $(WAV_WELCOME)

.PHONY: pushit welcome

# ==============================
##@ 💾 Backup
# ==============================

BACKUP_NAME	:=$(ROOT_DIR)_$(USER)_$(TIMESTAMP).zip
MOVE_TO		:= ~/Desktop/$(BACKUP_NAME)

backup: ffclean ## Creates a zip file of the project
	@if which zip > $(VOID); then \
		zip -r --quiet $(BACKUP_NAME) ./*; \
		mv $(BACKUP_NAME) $(MOVE_TO); \
		$(call INFO,$(NAME),compressed as: ,$(CYAN)$(UNDERLINE)$(MOVE_TO)$(RESET)); \
	else \
		$(call ERROR,Please install zip to use the backup feature); \
	fi

.PHONY: backup
