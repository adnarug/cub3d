NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Wall -Wextra #-fsanitize=address #-Werror
LIBMLX = lib/libmlx42.a
LIBS = $(LIBMLX) -lglfw -L $$HOME/.brew/Cellar/glfw/3.3.8/lib/ -framework OpenGL -framework AppKit

LIBFT = libft/
CC = gcc
SRC_FILES = utils/args_check \
			utils/get_next_line \
			utils/get_next_line_utils \
			utils/errors \
			utils/tools \
			utils/rgb_utils \
			utils/rgb_utils2 \
			map_parse/init_map \
			map_parse/init_map2 \
			map_parse/init_map3 \
			map_parse/extract_tex\
			map_parse/extract_tex2\
			map_parse/extract_tex3\
			map_parse/extract_tex4\
			map_parse/check_map \
			map_parse/check_map2 \
			mini_map/init_minimap \
			mini_map/upd_minimap \
			mini_map/minimap_tools \
			movement/key_hooks \
			movement/move_rotate \
			initialization/inits \
			initialization/free \
			raycasting/raycaster \
			raycasting/textures \
			main
DEF_COLOR = \033[0;80m
GREEN = \033[0;92m

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

OBJF = .cache_exists

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(LIBMLX) $(LIBS) $(LIBFT)/libft.a $(OBJ) -o $(NAME)
	@echo "$(GREEN)cub3D compiled$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p obj/map/
	@mkdir -p obj/utils/
	@mkdir -p obj/map_parse/
	@mkdir -p obj/initialization/
	@mkdir -p obj/mini_map/
	@mkdir -p obj/movement/
	@mkdir -p obj/raycasting/

clean:
	@rm -r $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf make $(NAME)
	@rm -rf cub3D
	@make fclean -C $(LIBFT)

bonus:
	@echo "Compiled with bonus!"

run:
	@make
	@./cub3D maps/basic.cub

re: fclean all

.PHONY: all, clean, fclean, re