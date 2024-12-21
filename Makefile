# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 10:28:35 by anebbou           #+#    #+#              #
#    Updated: 2024/12/21 00:38:45 by anebbou          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program Name
NAME = push_swap

# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I. -I$(LIBFT_DIR)/includes

# Libft Setup
LIBFT_DIR = Libft_GNL_Printf
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_REPO = https://github.com/Artnebs/Libft_GNL_Printf.git

# Source and Object Files
SRC = main.c parse_args.c init.c operations.c operations2.c operations2_cont.c utils.c sorting_small.c sorting_large.c costs_and_median.c
OBJ = $(SRC:.c=.o)

# Debug Mode
ifeq ($(DEBUG), 1)
    CFLAGS += -DDEBUG
endif

# Default Rule
all: $(LIBFT) $(NAME)

# Build the executable
$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compile object files
%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Build Libft
$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning Libft repository..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	@echo "Building Libft library..."
	@make -C $(LIBFT_DIR)

# Clean object files
clean:
	@echo "Cleaning object files..."
	rm -f $(OBJ)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make -C $(LIBFT_DIR) clean; \
	fi

# Clean all files
fclean: clean
	@echo "Cleaning $(NAME) and Libft..."
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		rm -rf $(LIBFT_DIR); \
		echo "Deleted Libft_GNL_Printf directory."; \
	fi

# Rebuild everything
re: fclean all

# Ensure makefile targets are not interpreted as filenames
.PHONY: all clean fclean re
