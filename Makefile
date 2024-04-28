RM = rm -f

CC = gcc
FLAGS_MLX =-Lmlx -lmlx_Linux -Llibft -lft -lXext -lX11 -lm -lz #-g3 -fsanitize=address
#FLAGS_MLX = -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror -g

LIBFT= -L libft -lft

NAME = Cub3D
SRC = main.c render.c keys.c check_extension.c open_map.c initialize_character.c check_map_validation.c\
duplicate_map.c floodfill.c rotate_vector2.c ray_collision.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(FLAGS) $(FLAGS_MLX) -c -o $@ $<

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(OBJ) $(FLAGS) $(FLAGS_MLX) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: bonus all clean fclean re
