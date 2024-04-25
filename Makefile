NAME = minishell

CC_FLAGS = -Wall -Werror -Wextra -g -I$(INCLUDES)
OTHER_LIBS = -lreadline -lncurses

INCLUDES = include/
LIBFT_FOLDER = $(INCLUDES)libft
LIBFT_A = $(INCLUDES)libft/libft.a

SRC_DIR = src/
SRC_NAME = tokeniser_main_test.c
SRC_NAME +=	tokeniser/ms_tokeniser_cmd.c\
			tokeniser/ms_tokeniser_main.c\
			tokeniser/ms_tokeniser_params.c\
			tokeniser/ms_tokeniser_utils.c
SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))

OBJ_DIR = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(patsubst %, $(OBJ_DIR)%, $(OBJ_NAME))
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
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