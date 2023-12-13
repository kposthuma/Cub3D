# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lvan-gef <lvan-gef@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/09/30 23:59:06 by lvan-gef      #+#    #+#                  #
#    Updated: 2023/12/12 18:00:47 by kposthum      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME := cub3d
CC := cc -Wall -Werror -Wextra -g3
# CC := cc -Wall -Werror -Wextra -g3 -fsanitize=address

SRCDIR := ./src
OBJDIR := ./obj

HEADERS := -I ./libft/include -I ./include
LIBFT := ./libft/libft.a

SRCS := main.c\
		error3d.c\
		parse3d.c\
		list3d.c
		
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)\

.PHONY: libft gnl clean fclean all re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo Making $(NAME)
	@$(CC) $(OBJS) $(HEADERS) $(LIBFT) $(LIBS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo Compiling $<
	@$(CC) $(HEADERS) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C ./libft

clean:
	@echo Removing object files $(NAME)
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@$(MAKE) clean -C ./libft

fclean: clean
	@echo Removing $(NAME)
	@rm -f $(NAME)
	@$(MAKE) fclean -C ./libft

re: fclean all
