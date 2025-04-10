# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ferda-si <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 17:40:26 by ferda-si          #+#    #+#              #
#    Updated: 2024/11/08 17:50:28 by ferda-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = src/main.c src/check_args.c src/utils.c

OBJS = $(FILES:src/%.c=objs/%.o)

CFLAGS          = -Wall -Werror -Wextra
NAME = phil

PRINTF = ft_printf/libftprintf.a
OBJS_PATH = objs/
FILES_PATH = src/

all: $(NAME) $(OBJS)

$(NAME): $(OBJS)
	@make -C ft_printf
	cc $(CFLAGS) -I headers -I ft_printf $(OBJS) $(PRINTF) -o $(NAME)

$(OBJS_PATH)%.o: $(FILES_PATH)%.c
	@mkdir -p objs
	cc $(CFLAGES) -I headers -I ft_printf -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C ft_printf clean

fclean: clean
	rm -f so_long ft_printf/libftprintf.a

re: fclean clean all
