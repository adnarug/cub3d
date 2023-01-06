NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Wall -Wextra -g #-fsanitize=address#-Wno-gnu-include-next -I/LeakSanitizer/include -L./LeakSanitizer/ -llsan -lc++ #-fsanitize=address #-Werror 
LIBMLX = lib/libmlx42.a
LIBS = $(LIBMLX) -lglfw -framework OpenGL -framework AppKit
LIBFT = libft/
CC = gcc
SRC_FILES = utils/args_check \
			utils/get_next_line \
			utils/get_next_line_utils \
			utils/errors \
			utils/tools \
			map_parse/init_map \
			map_parse/extract_tex\
			map_parse/extract_map \
			map_parse/check_map \
			main
DEF_COLOR = \033[0;80m
GREEN = \033[0;92m

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

OBJF = .cache_exists

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(LIBS) $(LIBFT)/libft.a $(OBJ) -o $(NAME)
	@echo "$(GREEN)cub3D compiled$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p obj/map/
	@mkdir -p obj/utils/
	@mkdir -p obj/map_parse/
	@mkdir -p obj/initializer/

clean:
	@rm -r $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf make $(NAME)
	@rm -rf cub3D
	@make fclean -C $(LIBFT)

run:
	@make
	@./cub3D maps/basic.cub

re: fclean all

.PHONY: all, clean, fclean, re