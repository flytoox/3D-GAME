# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aait-mal <aait-mal@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/26 21:42:53 by obelaizi          #+#    #+#              #
#    Updated: 2023/11/10 10:00:02 by aait-mal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/07 15:13:54 by aait-mal          #+#    #+#              #
#    Updated: 2023/08/06 17:23:39 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
SRC = $(wildcard  *.c Parsing/*.c gnl/*.c) 
OBJ = $(SRC:.c=.o)
HEADER = ./cub3d.h ./Libft/libft.h ./gnl/get_next_line.h
CC = cc
FLAGS = -Wall -Wextra -Werror

all : libft.a $(NAME)

libft.a :
	make -C Libft all bonus

$(NAME) :  $(OBJ) ./Libft/libft.a 
	$(CC) $(OBJ) $(FLAGS) ./Libft/libft.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -Imlx -c $< -o $@

clean :
	rm -rf $(OBJ)
	make -C Libft clean

fclean : clean
	rm -rf $(NAME)
	make -C Libft fclean

re : fclean all

.PHONY : all clean fclean re
