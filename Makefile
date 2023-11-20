# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 21:42:53 by obelaizi          #+#    #+#              #
#    Updated: 2023/11/20 15:25:10 by aait-mal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
HEADER = ./cub3d.h ./libft/libft.h ./get_next_line/get_next_line.h
SRC = $(wildcard  *.c parsing/*.c draw_utils/*.c mlx_utils/*.c ray_casting/*.c rendering_3d/*.c get_next_line/*.c) 
OBJ = $(SRC:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror

all : libft.a $(NAME)

libft.a :
	make -C libft all bonus

$(NAME) :  $(OBJ) ./libft/libft.a 
	$(CC) $(OBJ) $(FLAGS) ./libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ)
	make -C libft clean

fclean : clean
	rm -rf $(NAME)
	make -C libft fclean

re : fclean all

.PHONY : all clean fclean re
