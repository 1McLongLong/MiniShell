# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: touahman <touahman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 17:41:23 by touahman          #+#    #+#              #
#    Updated: 2024/03/02 19:27:16 by touahman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

SRCF = $(addprefix src/, main.c list_utils.c helper.c helper2.c handle_spaces.c lexer.c tokenizer.c tokenizer2.c syntax.c expand.c expand2.c fix_quotes.c \
			 token_utils.c remove_quotes.c redirect.c expand_redirect.c token_split.c exec_line.c heredoc.c)
GNL_SRCF = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
PRINTF_SRCF = $(addprefix printf/, ft_printf.c ft_putchar.c ft_putstr.c ft_putnbr.c ft_put_hex.c \
							ft_put_bighex.c ft_putnbr_u.c ft_print_add.c)
LIBFT_SRCF = $(addprefix libft/, ft_isalpha.c ft_atoi.c ft_calloc.c ft_isprint.c ft_memcpy.c ft_memset.c ft_strlcpy.c ft_strrchr.c ft_atoi.c \
						 ft_isalnum.c ft_isascii.c ft_memchr.c ft_strchr.c ft_strlen.c ft_tolower.c ft_bzero.c ft_isdigit.c ft_memcmp.c ft_strdup.c \
						 ft_strncmp.c ft_toupper.c ft_strlcat.c ft_memmove.c ft_strnstr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
						 ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c)

OBJF = $(SRCF:.c=.o)
GNL_OBJF = $(GNL_SRCF:.c=.o)
PRINTF_OBJF = $(PRINTF_SRCF:.c=.o)
LIBFT_OBJF = $(LIBFT_SRCF:.c=.o)

NAME = minishell

all : $(NAME)

$(NAME): $(OBJF) $(LIBFT_OBJF) $(GNL_OBJF) $(PRINTF_OBJF)
	@$(CC) $(CFLAGS) -lreadline $^ -o $@
	@echo "🚀 Mission is complete!"

%.o : %.c ./src/header.h ./printf/ft_printf.h ./gnl/get_next_line.h ./libft/libft.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJF) $(GNL_OBJF) $(PRINTF_OBJF) $(LIBFT_OBJF)
	@echo "BYE BYE 👋"

fclean: clean
	@rm -f $(NAME)
	@echo "BYE BYE MINISHELL👋"

re: fclean all

.PHONY : all clean fclean re
