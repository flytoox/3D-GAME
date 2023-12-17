# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 21:42:53 by obelaizi          #+#    #+#              #
#    Updated: 2023/12/17 15:30:43 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = ./game/cub3d.h ./game/libft/libft.h ./game/get_next_line/get_next_line.h
SRC = game/parsing/parsing0.c game/parsing/parsing1.c game/parsing/parsing_utils.c game/parsing/parsing_utils1.c game/parsing/split.c \
	game/get_next_line/get_next_line.c game/get_next_line/get_next_line_utils.c \
	game/draw_utils/draw_line.c game/draw_utils/draw_utils.c game/draw_utils/player_utils.c game/mlx_utils//mlx_pixel_put.c \
	game/mlx_utils//mlx_utils.c game/ray_casting/horizontal_intersect.c game/ray_casting/ray_casting.c \
	game/ray_casting/ray_casting_utils.c game/ray_casting/ray_casting_utils2.c game/ray_casting/vertical_intersect.c \
	game/rendering_3d/rendering.c game/rendering_3d/textures.c game/rendering_3d/update_player.c game/main.c game/map.c 
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

all : libft.a $(NAME)

libft.a :
	make -C ./game/libft all bonus

$(NAME) :  $(OBJ) ./game/libft/libft.a
	$(CC) $(OBJ) $(FLAGS) ./game/libft/libft.a ./mlx/libmlx.a  -lmlx -framework OpenGL -framework AppKit -o $(NAME) 

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
	make -C ./game/libft clean

fclean : clean
	rm -rf $(NAME)
	make -C ./game/libft fclean

re : fclean all

.PHONY : all clean fclean re
