# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngrasset <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 16:13:25 by ngrasset          #+#    #+#              #
#    Updated: 2018/04/17 17:45:07 by ngrasset         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

C_DIR = src

C_FILES = src/main.c src/camera.c src/v3.c src/threads.c src/ray.c

O_DIR =	.tmp/obj
O_FILES = $(C_FILES:$(C_DIR)%.c=$(O_DIR)%.o)

FLAGS = -Wall -Wextra -Werror -O3 -fsanitize=address
INCLUDES = -I ./include -I ./libft/includes -I./libmlx

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIB = -L./libft -lft -L./libmlx_linux -lmlx -lXext -lX11 -lm -pthread
endif
ifeq ($(UNAME_S), Darwin)
	LIB = -L./libft -lft -L./libmlx -lmlx -framework OpenGL -framework AppKit
endif

CC = clang

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $^ $(INCLUDES) $(LIB) -o $@

$(O_DIR)%.o: $(C_DIR)%.c
	@mkdir -p $(O_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -Rf $(O_DIR)

fclean: clean
	@rm $(NAME) || true
	@rm -Rf .tmp/

re: fclean all

.PHONY: clean all fclean re
