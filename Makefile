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

FILES = src/src/main.c src/src/check_args.c src/src/utils.c

OBJS = $(FILES:src/src/%.c=src/objs/%.o)

CFLAGS          = -Wall -Werror -Wextra
NAME = philo

OBJS_PATH = src/objs/
FILES_PATH = src/src/

all: $(NAME) $(OBJS)

$(NAME): $(OBJS)
	cc $(CFLAGS) -I src/headers  $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o: $(FILES_PATH)%.c
	@mkdir -p src/objs
	cc $(CFLAGS) -I src/headers -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_PATH)

fclean: clean
	 
	rm -rf $(OBJS_PATH)

re: fclean clean all