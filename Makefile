
NAME = mini_shell

CC_FLAGS = -Wall -Werror -Wextra -g -I$(INCLUDES)
OTHER_LIBS = -lreadline -lncurses

INCLUDES = include/
LIBFT_FOLDER = $(INCLUDES)libft
LIBFT_A = $(INCLUDES)libft/libft.a

SRC_DIR = src/
SRC_NAME = ms_main.c
SRC_NAME +=	env_handler/ms_env_var.c \
			env_handler/ms_env_utils_1.c \
			env_handler/ms_env_utils_2.c \
			env_handler/ms_env_builtins.c
SRC_NAME += commands/ms_exit.c \
			commands/ms_echo.c \
			commands/ms_cd.c
SRC_NAME += execution/ms_exec.c \
			execution/ms_exec_utils.c \
			execution/ms_exec_initfds.c \
			execution/ms_heredoc.c

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJ_DIR = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	cc $(CC_FLAGS) $< -c -o $@

$(OBJ_DIR)%.o:$(BONUS_DIR)%.c
	cc $(CC_FLAGS) $< -c -o $@

$(NAME): $(OBJ)
	@make full -C $(LIBFT_FOLDER)
	cc -o $(NAME) $(OBJ) $(LIBFT_A) $(OTHER_LIBS)

clean:
	@make clean -C $(LIBFT_FOLDER)
	rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_FOLDER)
	rm -f $(NAME)

all: $(NAME)

re: fclean all