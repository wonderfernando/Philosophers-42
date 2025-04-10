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

FILES = philo/src/main.c philo/src/check_args.c philo/src/utils.c

OBJS = $(FILES:philo/src/%.c=philo/objs/%.o)

CFLAGS          = -Wall -Werror -Wextra
NAME = Philosophers

OBJS_PATH = philo/objs/
FILES_PATH = philo/src/

all: $(NAME) $(OBJS)

$(NAME): $(OBJS)
	cc $(CFLAGS) -I philo/headers  $(OBJS) -o $(NAME)

$(OBJS_PATH)%.o: $(FILES_PATH)%.c
	@mkdir -p philo/objs
	cc $(CFLAGS) -I philo/headers -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_PATH)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJS_PATH)

re: fclean clean all