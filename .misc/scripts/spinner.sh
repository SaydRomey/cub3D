#!/bin/bash

# spin()
# {
# 	case $(( $1 % 10 )) in
# 		0) echo -n "⠁" ;;
# 		1) echo -n "⠃" ;;
# 		2) echo -n "⠇" ;;
# 		3) echo -n "⠧" ;;
# 		4) echo -n "⠷" ;;
# 		5) echo -n "⠿" ;;
# 		6) echo -n "⠷" ;;
# 		7) echo -n "⠧" ;;
# 		8) echo -n "⠇" ;;
# 		9) echo -n "⠃" ;;
# 	esac
# }

# start_spinner_until_file_exists()
# {
# 	local message="$1"
# 	local file="$2"
# 	local delay=0.1
# 	local spinpos=0
# 	echo -n "$message "
# 	while [ ! -f "$file" ]; do
# 		echo -ne "\r$(spin $spinpos) $message"
# 		spinpos=$((spinpos+1))
# 		sleep $delay
# 	done
# 	echo -e "\r$message Done."
# }

# start_spinner_until_file_exists "$@"


# # # # # # #
# with predefined colors

SPIN_COLOR="\033[38;5;208;1m" # spinner
TEXT_COLOR="\033[96;1m" # message text
RESET="\033[0m"

spin()
{
	case $(( $1 % 10 )) in
		0) echo -n "⠁" ;;
		1) echo -n "⠃" ;;
		2) echo -n "⠇" ;;
		3) echo -n "⠧" ;;
		4) echo -n "⠷" ;;
		5) echo -n "⠿" ;;
		6) echo -n "⠷" ;;
		7) echo -n "⠧" ;;
		8) echo -n "⠇" ;;
		9) echo -n "⠃" ;;
	esac
}

start_spinner_until_file_exists()
{
    local message="$1"
    local file="$2"
    local delay=0.1
    local spinpos=0
    echo -ne "${TEXT_COLOR}$message${RESET} "
    while [ ! -f "$file" ]; do
        echo -ne "\r${SPIN_COLOR}$(spin $spinpos)${RESET} ${TEXT_COLOR}$message${RESET}"
        spinpos=$((spinpos+1))
        sleep $delay
    done
    echo -e "\r${TEXT_COLOR}$message Done.${RESET}"
}

start_spinner_until_file_exists "$@"



# # # # # # # #
# # with parametrized colors (wip, the cursor gets between the animation and the msg..)

# # ANSI color codes

# RESET="\033[0m"
# SPIN_COLOR=$1
# TEXT_COLOR=$2
# MESSAGE=$3
# FILE=$4

# spin()
# {
# 	case $(( $1 % 10 )) in
# 		0) echo -n "${SPIN_COLOR}⠁${RESET}" ;;
# 		1) echo -n "${SPIN_COLOR}⠃${RESET}" ;;
# 		2) echo -n "${SPIN_COLOR}⠇${RESET}" ;;
# 		3) echo -n "${SPIN_COLOR}⠧${RESET}" ;;
# 		4) echo -n "${SPIN_COLOR}⠷${RESET}" ;;
# 		5) echo -n "${SPIN_COLOR}⠿${RESET}" ;;
# 		6) echo -n "${SPIN_COLOR}⠷${RESET}" ;;
# 		7) echo -n "${SPIN_COLOR}⠧${RESET}" ;;
# 		8) echo -n "${SPIN_COLOR}⠇${RESET}" ;;
# 		9) echo -n "${SPIN_COLOR}⠃${RESET}" ;;
# 	esac
# }

# start_spinner_until_file_exists()
# {
# 	local delay=0.1
# 	local spinpos=0
# 	echo -ne "  ${TEXT_COLOR}$MESSAGE "
# 	while [ ! -f "$FILE" ]; do
# 		echo -ne "\r$(spin $spinpos)"
# 		spinpos=$((spinpos+1))
# 		sleep $delay
# 	done
# 	echo -e "\r${TEXT_COLOR}$MESSAGE Done.${RESET}"
# }

# start_spinner_until_file_exists

# # and use this in the makefile

# # 
# # Colors
# SPIN_COLOR	:= "$(BOLD)$(BLUE)" # Blue for spinner
# TEXT_COLOR	:= "$(BOLD)$(YELLOW)" # Yellow for text
# SPIN_MSG	:= "Simulating compilation and linking for five seconds..."
# SPIN_FILE	:= ".testfile"
# SLEEP_TIME	:= 5

# spin:
# 	@$(REMOVE) $(SPIN_FILE)
# 	@echo "Starting a long-running task..."
# 	@./spinner.sh $(SPIN_COLOR) $(TEXT_COLOR) $(SPIN_MSG) $(SPIN_FILE) &
# 	@sleep $(SLEEP_TIME)
# 	@touch $(SPIN_FILE)
# 	@sleep 0.2
# 	@echo "Long-running task completed."

# .PHONY: spin
