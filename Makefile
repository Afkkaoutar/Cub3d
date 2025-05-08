CC = cc
FLAGS = -Wall -Wextra -Werror # -fsanitize=address -g

MLX_DIR = minilibx_opengl_20191021
INCLUDES = -I. -I$(MLX_DIR)

SRCS = main.c \
		parcing/parse.c \
		parcing/check_data.c \
		parcing/check_data2.c \
		parcing/map_init.c \
		parcing/extra_sauce.c \
		parcing/parse_2.c \
		parcing/parse_map2.c \
		parcing/mooore.c \
		parcing/more1.c \
		parcing/tools_2.c \
		parcing/tools.c \
		parcing/get_next_line.c \
		parcing/get_next_line_utils.c \
		parcing/parse_map.c \
    	recasting/tracing.c \
		recasting/tractools.c \
		recasting/recastinit.c \
		recasting/keys_control.c \
		recasting/keys_control2.c \
		recasting/keys_control3.c \
		recasting/player.c \
		recasting/cast.c \
		recasting/cast2.c \
		recasting/horizontal.c \
		recasting/vertical.c \
		set_textures/load_texts.c \
		set_textures/sprites.c \
		free_leaks.c

OBJS = $(SRCS:.c=.o)

NAME = cube3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c cube3d.h
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
