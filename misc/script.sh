#!/bin/bash

# Bash script to install Cub3d Dependency on MacOS

# Check if Brew is installed
if [ -d "$HOME/.brew" ]; then
    echo -e "\033[0;32mBrew is already installed\033[0;37m"
else
    read -p "Brew is not installed. Would you like to install it? (y/n): " choice
    if [ "$choice" = "y" ] || [ "$choice" = "Y" ]; then
        rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update
        echo -e "\033[0;36mBrew is now installed\033[0;37m"
    else
        echo "Brew installation skipped."
    fi
fi

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    read -p "CMake is not installed. Would you like to install it using brew? (y/n): " cmake_choice
    if [ "$cmake_choice" = "y" ] || [ "$cmake_choice" = "Y" ]; then
        brew install cmake
        echo -e "\033[0;36mCMake is now installed\033[0;37m"
    else
        echo "CMake installation skipped."
    fi
else
    echo -e "\033[0;32mCMake is already installed\033[0;37m"
fi

# Check if GLFW is installed in the specified directory
glfw_dir="$HOME/.brew/opt/glfw/lib/"
if [ -d "$glfw_dir" ]; then
    echo -e "\033[0;32mGLFW is already installed in $glfw_dir\033[0;37m"
else
    read -p "GLFW is not installed. Would you like to install it using brew? (y/n): " glfw_choice
    if [ "$glfw_choice" = "y" ] || [ "$glfw_choice" = "Y" ]; then
        brew install glfw
        echo -e "\033[0;36mGLFW is now installed\033[0;37m"
    else
        echo "GLFW installation skipped."
    fi
fi
