# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kposthum <kposthum@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/14 11:38:49 by kposthum      #+#    #+#                  #
#    Updated: 2023/12/25 20:13:07 by koen          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC := cc -Wall -Werror -Wextra -g3
# CC := cc -Wall -Werror -Wextra -g3 -fsanitize=address

SRCDIR := ./src
OBJDIR := ./obj

HEADERS := -I ./libft/include -I ./include -I ./MLX42/include
LIBFT := ./libft/libft.a
LIBMLX := ./MLX42/build/libmlx42.a

SRCS := main.c\
		error3d.c\
		parse3d.c\
		flag3d.c\
		list3d.c\
		map3d.c\
		maputils3d.c\
		color_texture3d.c\
		init3d.c\
		window3d.c\
		destroy3d.c\
		utils3d.c
		
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)\

.PHONY: libft gnl clean fclean all re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	@echo Making $(NAME)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo Compiling $<
	@$(CC) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./libft

$(LIBMLX):
	@git submodule init
	@git submodule update
	@cmake ./MLX42 -B ./MLX42/build && make -C ./MLX42/build -j4

clean:
	@echo Removing object files $(NAME)
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@rm -rf ./MLX42/build
	@$(MAKE) clean -C ./libft

fclean: clean
	@echo Removing $(NAME)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all
