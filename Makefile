# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emansoor <emansoor@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 07:44:35 by emansoor          #+#    #+#              #
#    Updated: 2024/08/07 14:10:27 by emansoor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC = ./src/

CFILES = $(SRC)fdf.c \
		$(SRC)gather_map_data_utils.c \
		$(SRC)gather_map_data.c \
		$(SRC)validate_map.c \
		$(SRC)mlx_control.c \
		$(SRC)draw_utils.c \
		$(SRC)draw.c \
		$(SRC)bresenhamn.c

OFILES = $(CFILES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -lglfw -ldl -pthread -lm

INCLUDES = -Iinclude -L"/usr/lib/x86_64-linux-gnu"
#INCLUDES = -Iinclude

LIBFT = ./libs/libft/libft.a

MLX = ./libs/MLX42/build/libmlx42.a

all: $(NAME)

$(NAME): $(MLX) $(OFILES)
	make -C ./libs/libft
	make bonus -C ./libs/libft
	$(CC) $(CFLAGS) $(OFILES) $(LIBFT) $(MLX) $(MLXFLAGS) $(INCLUDES) -o $(NAME) 

$(MLX):
	cd libs/MLX42 && cmake -B build && cd build && make
	
clean:
	make -C ./libs/libft clean
	make -C ./libs/MLX42/build clean
	rm -f $(OFILES)
	
fclean: clean
	make -C ./libs/libft fclean
	rm -rf ./libs/MLX42/build
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re