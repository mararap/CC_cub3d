# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marapovi <marapovi@student.42vienna.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/21 15:27:09 by marapovi          #+#    #+#              #
#    Updated: 2026/08/21 14:56:26 by marapovi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

NAME		:=	cub3D
MANDATORY_BIN	:=	.cub3D_mandatory
BONUS_BIN	:=	.cub3D_bonus

HEADER		:=	./include/cub3d.h
BONUS_HEADER	:=	./include/minimap_bonus.h

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

APP_SRC		:=	app/setup.c \
				app/cleanup.c \
				app/hooks.c

INPUT_SRC	:=	input/keys.c

UTILS_SRC	:=	utils/error.c

PARSING_SRC	:=	parsing/get_next_line.c \
				parsing/parsing.c \
				parsing/parsing_config.c \
				parsing/parsing_texture.c \
				parsing/parsing_color.c \
				parsing/parsing_map.c \
				parsing/parsing_validate.c \
				parsing/parsing_player.c

DRAWING_SRC	:=	drawing/raycast.c \
				drawing/image.c \
				drawing/draw_3d.c \
				drawing/draw_texture.c

COMMON_SRC	:=	main.c \
				$(APP_SRC) \
				$(INPUT_SRC) \
				$(UTILS_SRC) \
				$(PARSING_SRC) \
				$(DRAWING_SRC)
MANDATORY_SRC	:=	drawing/draw_overlay.c
BONUS_SRC		:=	drawing/bonus/draw_minimap_bonus.c \
					drawing/bonus/draw_cell_bonus.c


COMMON_SRC		:=	$(addprefix $(SRC_DIR)/,$(COMMON_SRC))
MANDATORY_SRC	:=	$(addprefix $(SRC_DIR)/,$(MANDATORY_SRC))
BONUS_SRC		:=	$(addprefix $(SRC_DIR)/,$(BONUS_SRC))
COMMON_OBJ		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(COMMON_SRC))
MANDATORY_OBJ	:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MANDATORY_SRC))
BONUS_OBJ		:=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BONUS_SRC))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(NAME)

.PHONY: all mandatory bonus clean fclean re libft

$(NAME): mandatory

mandatory: libft $(MANDATORY_BIN)
	@cmp -s $(MANDATORY_BIN) $(NAME) || cp $(MANDATORY_BIN) $(NAME)

bonus: libft $(BONUS_BIN)
	@cmp -s $(BONUS_BIN) $(NAME) || cp $(BONUS_BIN) $(NAME)

libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(LIBFT):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(BONUS_OBJ): $(BONUS_HEADER)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(MANDATORY_BIN): $(COMMON_OBJ) $(MANDATORY_OBJ) $(LIBFT)
	@echo "     🛠️  Linking executable..."
	@$(CC) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(MANDATORY_OBJ) \
		$(LDLIBS) -o $(MANDATORY_BIN)
	@printf "\n%b\n\n" "$$(cat docs/banner_refined.txt)"

$(BONUS_BIN): $(COMMON_OBJ) $(BONUS_OBJ) $(LIBFT)
	@echo "     Linking bonus executable..."
	@$(CC) $(CFLAGS) $(LDFLAGS) $(COMMON_OBJ) $(BONUS_OBJ) \
		$(LDLIBS) -o $(BONUS_BIN)
	@printf "\n%b\n\n" "$$(cat docs/banner_refined.txt)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "     🧽 cub3D	= clean."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
	@echo "     🧽 LIBFT 	= clean."

fclean: clean
	@$(RM) $(NAME) $(MANDATORY_BIN) $(BONUS_BIN)
	@echo "     🧹 cub3D executable removed."
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "     🧹 LIBFT library removed."

re: fclean all