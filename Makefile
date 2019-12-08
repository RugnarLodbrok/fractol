# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/05 20:27:05 by ksticks           #+#    #+#              #
#    Updated: 2019/11/21 22:00:31 by rpoetess         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = fractol
FLAGS = -Wall -Wextra -Werror

SRC = \
		src/app.c \
		src/controller.c \
		src/camera.c \
		src/framebuffer.c \
		src/palette.c \
		src/fractol.c \
		src/fractol_pix.c \
		src/it_estimator.c \
		src/fractol_v2.c \
		src/main.c

OPTION = -I. -Ilibft -Iminilibx_macos
OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : libft/libft.a minilibx_macos/libmlx.a $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(OPTION) -L minilibx_macos/ -lmlx -L libft/ -lft -framework OpenGL -framework AppKit
#	@$(CC) -o $(NAME) $(OBJ) $(OPTION) -L minilibx_macos/ -L libft/ -lft

%.o: %.c
	@echo compile $(<) "->" $(<:.c=.o)
	$(CC) $(FLAGS) -c $(<) -o $(<:.c=.o) $(OPTION)

libft/libft.a :
	make -C libft/

minilibx_macos/libmlx.a :
#	@echo skip mac
	make -C minilibx_macos

run : $(NAME)
	@./$(NAME)

clean :
	rm -f $(OBJ)
	make -C libft/ clean

fclean : clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx_macos/ clean

re : fclean all
