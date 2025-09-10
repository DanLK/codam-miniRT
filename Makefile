vpath %.c src:src/color:src/parser:src/hittables:src/vec:src/bonus

NAME = miniRT
BONUS_NAME = miniRT_bonus

COMMON_SRC = miniRT.c \
	  print_error.c \
	  print_struct.c \
	  ray.c \
	  viewport.c \
	  color_cal_lights.c \
	  color_intensity.c \
	  color_utils.c \
	  parser_atod.c \
	  parser_check_input.c \
	  parser_list_mgr.c \
	  parser_space_split.c \
	  parser_util.c \
	  parser.c \
	  render.c \
	  hits.c \
	  cylinder.c \
	  vec_ops.c \
	  vec_utils.c \
	  vec.c \

MANDATORY_ONLY_SRC = color_obj_mandatory.c \
	 		parser_fill_in_structs_1_mandatory.c \
			parser_fill_in_structs_2_mandatory.c \

BONUS_ONLY_SRC = color_cal_checkerboard_bonus.c \
			color_local_basis_bonus.c \
			color_obj_bonus.c \
			parser_check_input_bonus.c \
			parser_fill_in_structs_1_bonus.c \
			parser_fill_in_structs_2_bonus.c \
			print_error_bonus.c

SRC = $(COMMON_SRC) $(MANDATORY_ONLY_SRC)
BONUS_SRC = $(COMMON_SRC) $(BONUS_ONLY_SRC)

OBJ_DIR = ./obj
BONUS_OBJ_DIR = ./obj_bonus

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJ = $(BONUS_SRC:%.c=$(BONUS_OBJ_DIR)/%.o)

CFLAGS += -Wall -Werror -Wextra

MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
LIBMLX = ./MLX42

HEADERS = -Iinclude -I$(LIBFT_DIR) -I $(LIBMLX)/include
LIBS := $(LIBMLX)/build/libmlx42.a -lm -ldl -lglfw -pthread
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: libmlx42 $(NAME)

bonus: CFLAGS += -DBONUS
bonus: libmlx42 $(BONUS_NAME)

libmlx42: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(LIBMLX):
	git clone $(MLX42_REPO) $(LIBMLX)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBS) $(LIBFT) $(HEADERS)

$(BONUS_NAME): $(BONUS_OBJ) $(LIBFT)
	$(CC) -o $(BONUS_NAME) $(BONUS_OBJ) $(LIBS) $(LIBFT) $(HEADERS)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	rm -rf $(LIBMLX)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx42 bonus
