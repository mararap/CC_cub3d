# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/21 15:27:09 by marapovi          #+#    #+#              #
#    Updated: 2026/06/25 19:32:17 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

NAME		:=	cub3D

HEADER		:=	./include/cub3d.h

CC			:=	cc

# C PreProcessor flags - exclusively needed when compiling src files
CPPFLAGS	:=	-I include -I libft

# C compiler flags - needed for compiling src files AND for linking
# CFLAGS		:=	-Wall -Wextra -Werror -O2 -march=native -g
CFLAGS		:=	-Wall -Wextra -Werror

# Flags/Options passed to the linker
LDFLAGS		:=	-L libft

# Libraries to pass to the linker
LDLIBS 		:=	-lft -lmlx -lX11 -lXext -lm

# set RM to remove directories and containing files recursiveley
RM			:=	rm -rf

# UNIX archive utility for creating static library
# c to explicitly create the library and silence warning if its not there
# r to replace existing symbols (functions) in the library and/or add new
# s to create an index for the library so linker will find symbols quickly
# AR		:=	ar crs


# **************************************************************************** #
#                                   PATHS                                      #
# **************************************************************************** #

OBJ_DIR			:=		obj
SRC_DIR			:=		src
LIBFT_DIR		:=		libft
LIBFT			:=		$(LIBFT_DIR)/libft.a

SRC 	:= 		main.c \
				


SRC				:=		$(addprefix $(SRC_DIR)/,$(SRC))
OBJ				:=		$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: libft $(NAME)

.PHONY: all clean fclean re libft

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	@echo "     🛠️  Linking executable..."
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(NAME)
	@printf "\n%b\n\n" "$$(cat docs/banner_refined.txt)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "     🧽 cub3D	= clean."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "     🧽 LIBFT 		= clean."

fclean: clean
	@$(RM) $(NAME)
	@echo "     🧹 cub3D executable removed."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "     🧹 LIBFT library removed."

re: fclean all