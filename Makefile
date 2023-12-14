# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kposthum <kposthum@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/12/14 11:38:49 by kposthum      #+#    #+#                  #
#    Updated: 2023/12/14 18:47:44 by kposthum      ########   odam.nl          #
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
		list3d.c\
		map3d.c
		
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)\

.PHONY: libft gnl clean fclean all re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	@echo Making $(NAME)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) $(LIBMLX) -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo Compiling $<
	@$(CC) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./libft

$(LIBMLX):
	@git clone https://github.com/codam-coding-college/MLX42.git MLX42
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
