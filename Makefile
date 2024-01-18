# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kposthum <kposthum@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/14 11:38:49 by kposthum      #+#    #+#                  #
#    Updated: 2024/01/18 16:38:01 by kposthum      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC := cc -g3 -Wall -Werror -Wextra
#CC := cc -g3 -fsanitize=address -Wall -Werror -Wextra 

SRC_DIR = ./src
OBJ_DIR = ./obj

HEADERS = -I ./libft/include -I ./include -I ./MLX42/include
LIBFT = ./libft/libft.a
LIBMLX = ./MLX42/build/libmlx42.a

FILES	=	ft_strmapiteri \
			ft_isempty \
			ft_access \
			ft_accesstype \
			ft_arrdup \
			error \
			ft_color \
			ft_realloc \
			maputils3d \
			main \
			window3d \
			list3d \
			destroy3d \
			keyhooks3d \
			display3d \
			ray3d \
			init3d \
			color_texture3d \
			parser \
			reader \
			flags \
			validation \
			validation_utils \

vpath %.c	$(SRC_DIR) \
			$(SRC_DIR)/parser \
			$(SRC_DIR)/renderer \
			$(SRC_DIR)/utils \

SRC 	= ${addsuffix .c, $(FILES)}
OBJ 	= ${patsubst %.c, $(OBJ_DIR)/%.o, $(SRC)}

all: $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(HEADERS) -c $< -o $@
	@echo Compiling $<

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	@echo Making $(NAME)
	@$(CC) $(OBJ) $(HEADERS) $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft

$(LIBMLX):
	@git submodule init
	@git submodule update
	@cmake ./MLX42 -B ./MLX42/build
	@make -C ./MLX42/build -j4

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@echo Removing object files $(NAME)
	@rm -rf $(OBJ_DIR)
	@rm -rf ./MLX42/build
	@$(MAKE) clean -C ./libft

fclean: clean
	@echo Removing $(NAME)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: fclean all clean re
