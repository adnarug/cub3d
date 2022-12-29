NAME = cub3D
SRC_DIR = src/
OBJ_DIR = obj/
FLAGS = -Wall -Wextra -Werror
LIBMLX = lib/libmlx42.a
LIBS = $(LIBMLX) -lglfw -framework OpenGL -framework AppKit
LIBFT = libft/
CC = gcc
SRC_FILES = main
DEF_COLOR = \033[0;80m
GREEN = \033[0;92m

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

all: $(NAME)

OBJF = .cache_exists

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(FLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)cub3D compiled$(DEF_COLOR)"

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c | $(OBJF)
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJF):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p map/
	@mkdir -p map_parse/

clean:
	@rm -r $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -rf make $(NAME)
	@rm -rf cub3D
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re