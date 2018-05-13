# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbousque <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 10:27:09 by dbousque          #+#    #+#              #
#    Updated: 2016/01/02 12:12:13 by dbousque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libjson.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -f

SRC		=	srcs/get_helpers.c \
			srcs/get_helpers2.c \
			srcs/handle_x.c \
			srcs/handle_x2.c \
			srcs/json.c \
			srcs/json2.c \
			srcs/json_errors.c \
			srcs/read_free_json.c \
			libdodo_srcs/ft_strcmp.c \
			libdodo_srcs/ft_atol.c \
			libdodo_srcs/ft_atod.c \
			libdodo_srcs/ft_strncpy.c \
			libdodo_srcs/ft_putendl.c \
			libdodo_srcs/ft_putstr.c \
			libdodo_srcs/ft_lstaddend.c \
			libdodo_srcs/ft_putendl_fd.c

OBJ		=	$(SRC:.c=.o)

HEADERS	=	-I./

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
			ranlib $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $^
	printf "\e[32m[✔]\e[36m $@ "
	printf "\033[0m\n"

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
