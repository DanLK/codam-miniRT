NAME = miniRT
SRC = miniRT.c \
	  print_error.c \
	  print_struct.c \
	  ray.c \
	  color/color.c \
	  parser/parser_ato.c \
	  parser/parser_check_input.c \
	  parser/parser_fill_in_structs_1.c \
	  parser/parser_fill_in_structs_2.c \
	  parser/parser_space_split.c \
	  parser/parser_util.c \
	  parser/parser.c \
	  vec/vec.c \
	  vec/vec_ops.c \
	  vec/vec_utils.c

SRC_DIR = ./src
OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS += -Wall -Werror -Wextra -g

MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
LIBMLX = ./MLX42

HEADERS = -Iinclude -I$(LIBFT_DIR)
LIBS := $(LIBMLX)/build/libmlx42.a -lm
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: libmlx42 $(NAME)

libmlx42: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBMLX):
	git clone $(MLX42_REPO) $(LIBMLX)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) $(LIBFT) $(HEADERS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx42
