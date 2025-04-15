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
NAME = philo

OBJS_PATH = objs/
FILES_PATH = src/

all: $(NAME) $(OBJS)

$(NAME): $(OBJS)
	cc $(CFLAGS) -I headers  $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o: $(FILES_PATH)%.c
	@mkdir -p objs
	cc $(CFLAGS) -I headers -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_PATH)

re: fclean clean all