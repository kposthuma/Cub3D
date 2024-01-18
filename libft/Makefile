# **************************************************************************** #
#																			  #
#														 ::::::::			 #
#	Makefile										   :+:	:+:			 #
#													  +:+					 #
#	By: kposthum <kposthum@student.codam.nl>		 +#+					  #
#													+#+					   #
#	Created: 2022/10/06 16:04:34 by kposthum	  #+#	#+#				  #
#	Updated: 2023/06/22 13:49:39 by kposthum	  ########   odam.nl		  #
#																			  #
# **************************************************************************** #

CC = gcc -Wall -Werror -Wextra
NAME = libft.a
SRCS = 	ft_atoi.c\
		ft_atol.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_charcount.c\
		ft_free.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_islower.c\
		ft_isprint.c\
		ft_isspace.c\
		ft_isupper.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split_quotes.c\
		ft_split_whitespace.c\
		ft_split.c\
		ft_str_of_strlen.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strcmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c\
		ft_printf.c\
		ft_printf_write.c\
		ft_printf_putptr.c\
		ft_print_charpp.c\
		get_next_line.c\
		get_next_line_utils.c

HEADERS	:= -I ./include
SRCDIR := ./src
OBJDIR := ./obj
OBJS :=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
SRCS := $(addprefix $(SRCDIR)/,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo Making $(NAME)
	@ar -cr $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(HEADERS) -c $< -o $@

clean:
	@echo Removing object files libft
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)

fclean: clean
	@echo Removing $(NAME)
	@rm -f $(NAME)

re:		fclean all

.PHONY: clean fclean all re