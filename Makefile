vpath %.c src:src/color:src/parser:src/sphere:src/vec

NAME = miniRT
SRC = miniRT.c \
	  print_error.c \
	  print_struct.c \
	  ray.c \
	  viewport.c \
	  color_intensity.c \
	  color_utils.c \
	  color.c \
	  parser_atod.c \
	  parser_check_input.c \
	  parser_fill_in_structs_1.c \
	  parser_fill_in_structs_2.c \
	  parser_space_split.c \
	  parser_util.c \
	  parser.c \
	  render.c \
	  sphere.c \
	  vec_ops.c \
	  vec_utils.c \
	  vec.c \

OBJ_DIR = ./obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS += -Wall -Werror -Wextra

MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
LIBMLX = ./MLX42

HEADERS = -Iinclude -I$(LIBFT_DIR) -I $(LIBMLX)/include
LIBS := $(LIBMLX)/build/libmlx42.a -lm -ldl -lglfw -pthread
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: libmlx42 $(NAME)

libmlx42: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBMLX):
	git clone $(MLX42_REPO) $(LIBMLX)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) $(LIBFT) $(HEADERS)

$(OBJ_DIR)/%.o: %.c
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
